#!/usr/bin/env bash
# Battle subsystem: replace readable Thumb with verified semantic C.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
LIMIT="${1:-10}"
shift || true

CONVERTED=$(python3 tools/decomp/battle_semantic_batch.py "$LIMIT" "$@" 2>&1 | tee /dev/stderr | tail -1)

if [ "${CONVERTED:-0}" -gt 0 ]; then
  make compare
fi
python3 tools/decomp/progress.py --write
