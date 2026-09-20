#!/usr/bin/env bash
# Deterministic Phase 3b pass: patterns + cleaned m2c. No API key.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
exec python3 tools/decomp/script_first.py "$@"
