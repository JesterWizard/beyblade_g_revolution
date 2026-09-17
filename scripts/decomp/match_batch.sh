#!/usr/bin/env bash
# Autonomous batch: triage N → verify asm bytes → integrate → compare → commit.
# Usage: scripts/decomp/match_batch.sh [count]
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

COUNT="${1:-10}"
LOG_DIR="$ROOT/mizuchi-output"
LOG="$LOG_DIR/match-batch-$(date +%Y%m%d-%H%M%S).log"
INTEGRATE="$ROOT/scripts/decomp/integrate_match.py"
VERIFY="$ROOT/scripts/decomp/verify_asm_bytes.py"

mkdir -p "$LOG_DIR"

if [[ ! -f scripts/decomp/verify_asm_bytes.py ]]; then
  echo "error: missing $VERIFY" >&2
  exit 1
fi

echo "==> Match batch: up to $COUNT functions" | tee "$LOG"

# Full triage list (skip already-matched); try easy functions first, scan all 633.
mapfile -t CANDIDATES < <(
  python3 scripts/decomp/triage_functions.py -n 633 --json \
    | python3 -c "import json,sys; print('\n'.join(json.load(sys.stdin)))"
)

MATCHED=0
FAILED=0
INTEGRATED=()

for fn in "${CANDIDATES[@]}"; do
  [[ "$MATCHED" -ge "$COUNT" ]] && break
  asm="asm/nonmatchings/${fn}.s"
  [[ -f "$asm" ]] || continue
  if [[ -f "asm/matchings/${fn}.s" ]]; then
    continue
  fi
  echo "--- $fn" | tee -a "$LOG"
  if ! python3 "$VERIFY" "$fn" >>"$LOG" 2>&1; then
    echo "skip $fn (cannot integrate)" | tee -a "$LOG"
    FAILED=$((FAILED + 1))
    continue
  fi
  python3 "$INTEGRATE" "$fn" >>"$LOG" 2>&1
  INTEGRATED+=("$fn")
  MATCHED=$((MATCHED + 1))
  echo "integrated $fn" | tee -a "$LOG"
done

if [[ "$MATCHED" -eq 0 ]]; then
  echo "==> No functions integrated (candidates exhausted or verify failed)" | tee -a "$LOG"
  exit 1
fi

echo "==> make compare" | tee -a "$LOG"
if ! make compare >>"$LOG" 2>&1; then
  echo "==> FAILED make compare — not committing" | tee -a "$LOG"
  exit 2
fi

TOTAL=$(python3 -c "import json; print(len(json.load(open('build/matched.json'))['functions']))")
LIST=$(IFS=, ; echo "${INTEGRATED[*]}")

# Status log
{
  echo ""
  echo "### $(date +%Y-%m-%d) — match_batch (+${MATCHED}, ${TOTAL}/633 linked)"
  echo "- Functions: \`${LIST//,/\`, \`}\`"
  echo "- make compare: OK"
} >> documentation/decomp-status.md

python3 scripts/decomp/report_status.py | tee -a "$LOG"

if git rev-parse --git-dir >/dev/null 2>&1; then
  echo "==> git commit" | tee -a "$LOG"
  git add \
    asm/matchings/ \
    asm/rom.s asm/rom_tail.s asm/rom_gap_*.s asm/rom_layout.ld \
    build/matched.json \
    documentation/decomp-status.md \
    documentation/decomp-progress.json \
    documentation/decomp-progress.svg \
    README.md 2>/dev/null || true
  git add -u asm/rom_gap_*.s 2>/dev/null || true
  git commit -m "$(cat <<EOF
decomp: match batch (+${MATCHED} functions, ${TOTAL}/633 total)

Integrate ${LIST}
make compare: OK
EOF
)" | tee -a "$LOG"
fi

echo "==> Done: ${MATCHED} integrated, ${TOTAL} total linked" | tee -a "$LOG"
echo "==> Log: $LOG"
