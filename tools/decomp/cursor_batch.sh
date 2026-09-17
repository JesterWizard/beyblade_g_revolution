#!/usr/bin/env bash
# Cursor-native batch: triage → m2c → permuter-free verify loop.
# No npm / Anthropic API required — the Cursor agent writes/fixes C.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
COUNT="${1:-5}"
LOG="$ROOT/mizuchi-output/cursor-batch-$(date +%Y%m%d-%H%M%S).log"
mkdir -p mizuchi-output

echo "==> Cursor batch: triage top $COUNT functions" | tee "$LOG"
python3 tools/decomp/triage_functions.py -n "$COUNT" | tee -a "$LOG"

# Ensure m2c
M2C_PY="tools/m2c/m2c.py"
if [ ! -f "$M2C_PY" ]; then
  echo "==> Cloning m2c" | tee -a "$LOG"
  git clone --depth 1 https://github.com/matt-kempster/m2c tools/m2c
fi

echo "==> m2c seeds (agent may refine)" | tee -a "$LOG"
while read -r fn; do
  asm="asm/nonmatchings/${fn}.s"
  [ -f "$asm" ] || continue
  out="mizuchi-output/${fn}.c"
  echo "--- $fn" | tee -a "$LOG"
  tail -n +5 "$asm" | PYTHONPATH=tools/m2c python3 "$M2C_PY" - > "$out" 2>>"$LOG" || true
  if [ -s "$out" ] && ! grep -q 'Decompilation failure' "$out"; then
    echo "wrote $out" | tee -a "$LOG"
    python3 tools/decomp/match_function.py "$fn" "$out" >>"$LOG" 2>&1 || true
  fi
done < <(python3 tools/decomp/triage_functions.py -n "$COUNT" --json | python3 -c "import json,sys; print('\n'.join(json.load(sys.stdin)))")

python3 tools/decomp/report_status.py | tee -a "$LOG"
echo "==> Log: $LOG"
