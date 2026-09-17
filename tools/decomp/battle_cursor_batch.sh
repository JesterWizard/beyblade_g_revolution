#!/usr/bin/env bash
# m2c + verify battle_scan candidates (no API key).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
COUNT="${1:-5}"
LOG="$ROOT/mizuchi-output/battle-cursor-$(date +%Y%m%d-%H%M%S).log"
mkdir -p mizuchi-output
M2C_PY="tools/m2c/m2c.py"

echo "==> Battle cursor batch: top $COUNT by battle_scan" | tee "$LOG"
mapfile -t FUNCS < <(python3 scripts/decomp/battle_scan.py -n "$COUNT" --json | python3 -c "import json,sys; print('\n'.join(json.load(sys.stdin)))")

for fn in "${FUNCS[@]}"; do
  asm="asm/nonmatchings/${fn}.s"
  [ -f "$asm" ] || continue
  out="mizuchi-output/${fn}.c"
  echo "--- $fn" | tee -a "$LOG"
  tail -n +5 "$asm" | PYTHONPATH=tools/m2c python3 "$M2C_PY" - > "$out" 2>>"$LOG" || true
  if [ -s "$out" ] && ! grep -q 'Decompilation failure' "$out"; then
    echo "wrote $out" | tee -a "$LOG"
    python3 scripts/decomp/match_function.py "$fn" "$out" >>"$LOG" 2>&1 || true
  fi
done

python3 scripts/decomp/report_status.py | tee -a "$LOG"
echo "==> Log: $LOG"
