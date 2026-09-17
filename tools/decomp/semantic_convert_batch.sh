#!/usr/bin/env bash
# Replace opcode-embedded stubs with byte-matched semantic C where possible.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
LIMIT="${1:-30}"
shift || true

python3 scripts/decomp/semantic_convert_batch.py "$LIMIT" "$@"
# Examples:
#   scripts/decomp/semantic_convert_batch.sh 30 --pool-free-only
#   scripts/decomp/semantic_convert_batch.sh 10 --battle
