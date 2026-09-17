#!/usr/bin/env python3
"""Verify a function can be integrated (Luvdis asm or baserom slice)."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from asm_bytes import integration_plan  # noqa: E402


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function", help="sub_0802B90C")
    args = parser.parse_args()

    plan = integration_plan(args.function)
    if plan is None:
        print(f"FAIL {args.function}", file=sys.stderr)
        return 2
    mode, size = plan
    print(f"OK {args.function} ({size} bytes, {mode})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
