#!/usr/bin/env python3
"""Sweep agbcc optimisation/flag sets for a parked seed.

Byte-mismatch tails are often just a different optimisation level or a
register-move pass: the retail build may have used -O1/-O0 or
-foptimize-register-move for a file.  Compiles the seed under a matrix of flag
sets (both agbcc and old_agbcc) and reports any byte-exact MATCH.

usage: flag_sweep.py <fn> <seed.c> [<fn2> <seed2.c> ...]
"""
from __future__ import annotations

import re
import sys
import tempfile
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
import match_function as mf  # noqa: E402

CMP = re.compile(r"^\s*/\*\s*match-compiler:")

FLAGSETS = [
    [],
    ["-O1"],
    ["-O0"],
    ["-Os"],
    ["-O3"],
    ["-foptimize-register-move"],
    ["-fregmove"],
    ["-fprologue-bugfix"],
    ["-O1", "-foptimize-register-move"],
    ["-fargument-noalias"],
    ["-fstrict-aliasing"],
    ["-fno-strict-aliasing"],
]


def variants(src: str, compiler: str) -> str:
    if compiler == "old_agbcc":
        return src if CMP.match(src) else "/* match-compiler: old_agbcc */\n" + src
    return "\n".join(l for l in src.splitlines() if not CMP.match(l)) + "\n"


def sweep(fn: str, seed: Path) -> list[str]:
    size = mf.reference_size(fn)
    want = mf.retail_bytes(fn, size)
    src = seed.read_text()
    hits = []
    for compiler in ("agbcc", "old_agbcc"):
        for flags in FLAGSETS:
            with tempfile.TemporaryDirectory() as tmp:
                c_path = Path(tmp) / f"{fn}.c"
                c_path.write_text(variants(src, compiler))
                obj = Path(tmp) / "s.o"
                try:
                    mf.compile_c(c_path, obj, quiet=True, extra_flags=flags)
                except Exception as exc:  # noqa: BLE001
                    print(f"    {fn} [{compiler} {' '.join(flags)}] compile failed: {exc}")
                    continue
                got = mf.normalize_compiled(mf.obj_text_bytes(obj, fn), size)
                if got == want:
                    print(f"*** MATCH {fn} [{compiler} {' '.join(flags) or '(default)'}]", flush=True)
                    hits.append((compiler, flags))
                    out = Path(f"/tmp/flag_sweep_{fn}_{compiler}_{'_'.join(flags) or 'def'}.c")
                    out.write_text(src)
    print(f"{fn}: hits={hits}", flush=True)
    return hits


if __name__ == "__main__":
    args = sys.argv[1:]
    for i in range(0, len(args), 2):
        sweep(args[i], Path(args[i + 1]))
