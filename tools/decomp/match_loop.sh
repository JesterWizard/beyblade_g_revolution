#!/usr/bin/env bash
# Run match_batch until all 633 functions linked or no progress possible.
# Usage: scripts/decomp/match_loop.sh [per_batch]
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

PER_BATCH="${1:-10}"
TARGET=633
BATCH="$ROOT/scripts/decomp/match_batch.sh"

while true; do
  TOTAL=$(python3 -c "import json; print(len(json.load(open('build/matched.json'))['functions']))")
  echo "==> match_loop: ${TOTAL}/${TARGET} linked"
  if [[ "$TOTAL" -ge "$TARGET" ]]; then
    echo "==> Phase 1 complete: all functions linked"
    exit 0
  fi
  if ! bash "$BATCH" "$PER_BATCH"; then
    echo "==> match_loop: batch returned failure at ${TOTAL}/${TARGET}"
    exit 1
  fi
done
