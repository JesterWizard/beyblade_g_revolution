#!/usr/bin/env python3
"""Preprocess a C file into ctx.c for m2c / Mizuchi context."""

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

CPPFLAGS = [
    "-I", str(ROOT / "include"),
    "-I", str(ROOT / "tools" / "agbcc" / "include"),
    "-I", str(ROOT / "tools" / "agbcc"),
    "-nostdinc",
    "-undef",
    "-Wno-trigraphs",
    "-DMODERN=0",
]


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} <file.c>", file=sys.stderr)
        return 1

    src = Path(sys.argv[1])
    if not src.is_file():
        print(f"missing file: {src}", file=sys.stderr)
        return 1

    out = ROOT / "ctx.c"
    with out.open("w") as fout:
        subprocess.run(
            ["gcc", "-E", "-P", *CPPFLAGS, str(src)],
            check=True,
            stdout=fout,
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
