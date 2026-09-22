#!/usr/bin/env python3
"""Symbolise literal addresses in parked WIP seeds and re-score.

agbcc folds arithmetic on bare integer literals (e.g. a second global two words
from the first becomes `add r0, #8`), which is a very common cause of a
same-size DIFF.  Retail addressed those globals through distinct symbols.
This rewrites each `0x03xxxxxx` / `0x04xxxxxx` / `0x05xxxxxx` / `0x08xxxxxx`
literal in the seed into a `gData_XXXXXXXX` symbol (auto-registered in
asm/data_symbols.s) and re-scores under both compilers.

usage: symbolize_sweep.py [fn ...]
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from opcode_stubs import file_kind  # noqa: E402

DATA_S = Path("asm/data_symbols.s")
DATA_H = Path("include/data_symbols.h")
LIT_RE = re.compile(r"0x0[0-9A-Fa-f]{7}\b")
CMP = re.compile(r"^\s*/\*\s*match-compiler:")


def is_addr(s: str) -> bool:
    v = int(s, 16)
    return v >= 0x02000000


def symbolise(src: str, add_h: bool) -> str | None:
    lits = [m.group(0) for m in LIT_RE.finditer(src)]
    lits = [l for l in dict.fromkeys(lits) if is_addr(l)]
    if not lits:
        return None
    out = src
    for l in lits:
        out = re.sub(rf"\b{re.escape(l)}\b", f"gData_{l[2:].upper()}", out)
    if "data_symbols.h" not in out:
        out = out.replace('#include "global.h"', '#include "global.h"\n#include "data_symbols.h"', 1)
    return out


def register(lits: list[str]) -> None:
    t = DATA_S.read_text()
    h = DATA_H.read_text()
    for l in lits:
        name = f"gData_{l[2:].upper()}"
        if name not in t:
            t = t.rstrip("\n") + f"\nSET_DATA {name}, {l}\n"
        if name not in h:
            h = h.replace(
                "extern u8 gData_03000108[];",
                f"extern u8 gData_03000108[];\nextern u8 {name}[];",
            )
    DATA_S.write_text(t)
    DATA_H.write_text(h)


def score(fn: str, text: str, compiler: str) -> str:
    if compiler == "old_agbcc":
        if not CMP.match(text):
            text = "/* match-compiler: old_agbcc */\n" + text
    else:
        text = "\n".join(l for l in text.splitlines() if not CMP.match(l)) + "\n"
    tmp = Path("/tmp/sym_sweep") / f"{fn}_{compiler}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_text(text)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True,
    )
    out = r.stdout.strip().splitlines()
    return out[0] if out else "?"


def main() -> int:
    only = set(sys.argv[1:])
    hits = []
    for p in sorted(Path("src/decompiled").glob("sub_*.c")):
        fn = p.stem
        if only and fn not in only:
            continue
        matched = Path(f"src/matched/{fn}.c")
        if matched.exists() and file_kind(matched) == "semantic":
            continue
        src = p.read_text()
        sym = symbolise(src, True)
        if not sym:
            continue
        lits = sorted({m.group(0) for m in LIT_RE.finditer(src)})
        register([l for l in lits if is_addr(l)])
        for comp in ("agbcc", "old_agbcc"):
            tag = score(fn, sym, comp)
            if tag.startswith("MATCH"):
                print(f"*** MATCH {fn} [{comp}] symbolised", flush=True)
                hits.append((fn, comp))
                Path(f"/tmp/sym_sweep/{fn}_{comp}_MATCH.c").write_text(sym)
    print("HITS:", hits)
    return 0


if __name__ == "__main__":
    sys.exit(main())
