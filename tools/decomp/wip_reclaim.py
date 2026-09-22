#!/usr/bin/env python3
"""Reclaim parked WIP seeds that already MATCH.

Some parked `src/wip/*.c` files are byte-exact already (often thanks to a
`/* match-compiler: old_agbcc */` line inside the file that a later sweep added
but never integrated).  Score each parked seed under both compilers and
integrate every MATCH.

usage: wip_reclaim.py [--dry-run]
"""
from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
import match_function as mf  # noqa: E402
from opcode_stubs import file_kind  # noqa: E402


def main() -> int:
    dry = "--dry-run" in sys.argv
    hits = []
    for p in sorted(Path("src/wip").glob("sub_*.c")):
        fn = p.stem
        matched = Path(f"src/matched/{fn}.c")
        if matched.exists() and file_kind(matched) == "semantic":
            continue
        src = p.read_text()
        compilers = ["agbcc"]
        if "old_agbcc" not in src:
            compilers.append("old_agbcc")
        tmp = Path("/tmp/wip_reclaim")
        tmp.mkdir(parents=True, exist_ok=True)
        for comp in compilers:
            text = src
            if comp == "old_agbcc":
                text = "/* match-compiler: old_agbcc */\n" + src
            c = tmp / f"{fn}.c"
            c.write_text(text)
            r = subprocess.run(
                [sys.executable, "tools/decomp/match_function.py", fn, str(c)],
                capture_output=True, text=True,
            )
            if r.stdout.startswith("MATCH"):
                print(f"*** MATCH {fn} [{comp}]", flush=True)
                hits.append((fn, comp, text))
                break
    print(f"reclaim hits: {[ (f,c) for f,c,_ in hits ]}")
    if dry:
        return 0
    for fn, comp, text in hits:
        src = Path(f"src/wip/{fn}.c")
        src.write_text(text)
        r = subprocess.run(
            [sys.executable, "tools/decomp/integrate_c.py", fn, f"@{src}"],
            capture_output=True, text=True,
        )
        print(f"integrate {fn}: {r.stdout.strip().splitlines()[-1] if r.stdout else r.stderr.strip()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
