#!/usr/bin/env python3
"""Restore a function to verified readable Thumb from asm/matchings or baserom."""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from readable_asm import guess_readable_asm  # noqa: E402
from integrate_c import verify  # noqa: E402

INTEGRATE = ROOT / "tools" / "decomp" / "integrate_c.py"
MATCH_ASM = ROOT / "asm" / "matchings"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    args = parser.parse_args()

    cand = guess_readable_asm(args.function)
    if cand is None:
        print(f"error: no asm for {args.function}", file=sys.stderr)
        return 1

    with subprocess.Popen(
        [
            sys.executable,
            str(INTEGRATE),
            args.function,
            cand.body,
            "--kind",
            "asm",
            "--note",
            "restore-readable",
            "--skip-compare",
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    ) as proc:
        out = proc.communicate()[0]
        if proc.returncode != 0:
            print(out, file=sys.stderr)
            return proc.returncode

    path = ROOT / "src" / "matched" / f"{args.function}.c"
    if not verify(args.function, path):
        print(f"error: restored {args.function} does not verify", file=sys.stderr)
        return 1

    print(f"restored {args.function} to readable Thumb")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
