#!/usr/bin/env python3
"""Collapse the duplicated header block the integrator prepends to `src/matched/*.c`.

The integrator writes

    #include "global.h"
    #include "ram_map.h"
    #include "battle.h"

    // @ 0x080617c4
    /* match-compiler: old_agbcc */
    #include "global.h"          <- duplicate

    // @ 0x080617c4            <- duplicate
    // real explanation ...

which is harmless but noisy. This removes the second `#include "global.h"` together
with the blank line and the repeated address comment that follow it, keeping the first
address comment and the compiler marker.

  python3 tools/decomp/fix_dup_headers.py --dry-run
  python3 tools/decomp/fix_dup_headers.py
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"

_INCLUDE = re.compile(r'^#include "global\.h"\s*$')
_ADDR = re.compile(r"^// @ 0x[0-9a-fA-F]{8}\s*$")


def fix(text: str) -> tuple[str, bool]:
    lines = text.splitlines(keepends=True)
    seen = 0
    for i, line in enumerate(lines):
        if not _INCLUDE.match(line):
            continue
        seen += 1
        if seen == 1:
            continue
        j = i + 1
        while j < len(lines) and lines[j].strip() == "":
            j += 1
        if j < len(lines) and _ADDR.match(lines[j].strip() + "\n"):
            j += 1
        if j < len(lines) and lines[j].strip() == "" and j == i + 2:
            # keep one blank line between the marker and the real comment
            pass
        return "".join(lines[:i] + lines[j:]), True
    return text, False


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    changed = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        text = path.read_text()
        new, did = fix(text)
        if not did:
            continue
        changed.append(path.relative_to(ROOT))
        if not args.dry_run:
            path.write_text(new)
    for p in changed:
        print(("would fix " if args.dry_run else "fixed ") + str(p))
    print(f"{len(changed)} file(s) {'to fix' if args.dry_run else 'fixed'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
