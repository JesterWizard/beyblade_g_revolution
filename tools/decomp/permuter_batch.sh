#!/usr/bin/env bash
# Sequential bounded permuter runs; --no-integrate so the caller integrates serially.
cd /home/username/Github/beyblade_g_revolution
SECS="${1:-200}"
JOBS="${2:-4}"
shift 2 || true
FN_LIST=("$@")
for fn in "${FN_LIST[@]}"; do
  echo "================ $fn (budget ${SECS}s, jobs ${JOBS}) ================"
  python3 tools/decomp/permuter/auto.py "$fn" --no-integrate --seconds "$SECS" --jobs "$JOBS"
  echo "---- exit $? ----"
done
echo "PERMUTER BATCH DONE"
