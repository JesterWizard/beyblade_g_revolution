#!/usr/bin/env bash
# Phase 2 RAM map pass: rescan baserom pools, refresh asm pool + C header + docs.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

echo "==> RAM map pass (scan + emit asm/h/doc)"
python3 tools/scan_ram_literals.py --emit-asm --emit-h --emit-doc

echo "==> make compare"
make compare

echo "==> Phase 2 pass complete"
