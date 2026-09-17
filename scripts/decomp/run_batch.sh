#!/usr/bin/env bash
# Run Mizuchi on the next N easiest non-matching functions.
# Usage: scripts/decomp/run_batch.sh [count]
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

COUNT="${1:-10}"
MIZ="$ROOT/tools/mizuchi"
LOG="$ROOT/mizuchi-output/batch-$(date +%Y%m%d-%H%M%S).log"
STATUS="$ROOT/documentation/decomp-status.md"

mkdir -p mizuchi-output documentation

if [ ! -d "$MIZ" ]; then
  echo "error: Mizuchi not installed — run scripts/setup.sh" >&2
  exit 1
fi

if [ ! -f beyblade_g_revolution.map ]; then
  echo "==> Building map file"
  make compare
fi

python3 scripts/decomp/make_prompts.py -n "$COUNT"

echo "==> Batch decomp: $COUNT function(s)" | tee "$LOG"
echo "    Log: $LOG"

set +e
(
  cd "$MIZ"
  npm start -- index-codebase --config "$ROOT/mizuchi.yaml" --skip-embeddings
  npm start -- run --config "$ROOT/mizuchi.yaml"
) 2>&1 | tee -a "$LOG"
BATCH_RC=${PIPESTATUS[0]}
set -e

if [ "$BATCH_RC" -eq 0 ]; then
  echo "- [x] batch run finished ($(date -Iseconds)) — see $LOG" >> "$STATUS"
else
  echo "- [ ] batch run failed ($(date -Iseconds)) — see $LOG" >> "$STATUS"
fi

echo "" | tee -a "$LOG"
echo "==> Verifying ROM" | tee -a "$LOG"
make compare 2>&1 | tee -a "$LOG"

python3 scripts/decomp/report_status.py | tee -a "$LOG"
echo "==> Done. Summary: documentation/decomp-status.md"
