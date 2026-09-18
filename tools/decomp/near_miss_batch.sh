#!/usr/bin/env bash
# Try semantic C on readable-Thumb near-misses; make compare at end.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
LIMIT="${1:-20}"
EXTRA=()
if [[ "${2:-}" == "--seeds-only" ]]; then
  EXTRA+=(--seeds-only)
fi
python3 tools/decomp/near_miss_batch.py "$LIMIT" "${EXTRA[@]}"
make compare
