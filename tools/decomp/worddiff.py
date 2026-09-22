#!/usr/bin/env python3
"""Word-aligned retail-vs-compiled view for a hand-matching session.

  python3 tools/decomp/worddiff.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c

Runs `match_function.py --full`, pulls the retail/compiled hex out of the DIFF, and
prints them as one 16-bit word per line with the differing words flagged. Much easier
to read than the single-line hex blob when only a couple of instructions differ.
"""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def blob(line: str) -> bytes | None:
    """Extract the hex payload from a `-`/`+` diff line."""
    m = re.match(r"^[+-]?([0-9a-f]+)$", line.strip())
    if not m:
        return None
    return bytes.fromhex(m.group(1))


def main() -> int:
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    fn, c_path = sys.argv[1], sys.argv[2]
    out = subprocess.run(
        ["python3", "tools/decomp/match_function.py", fn, c_path, "--full"],
        cwd=ROOT, capture_output=True, text=True,
    ).stdout
    header = "\n".join(out.splitlines()[:3])
    retail = compiled = None
    for line in out.splitlines():
        if line.startswith("--- retail"):
            continue
        if line.startswith("-"):
            retail = blob(line[1:])
        elif line.startswith("+"):
            compiled = blob(line[1:])
    print(header)
    if retail is None or compiled is None:
        print(out)
        return 1
    print(f"retail {len(retail)}B  compiled {len(compiled)}B")
    print(" off  retail compiled")
    for i in range(0, max(len(retail), len(compiled)), 2):
        r = retail[i:i + 2].hex() or "--"
        c = compiled[i:i + 2].hex() or "--"
        same = r == c
        print(f"{i:04x}  {r:>6} {c:>6}   {'' if same else '<-- DIFF'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
