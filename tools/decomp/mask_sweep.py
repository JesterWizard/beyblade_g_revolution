#!/usr/bin/env python3
"""Rewrite literal clear-bit masks into a `s32` local and re-score.

agbcc folds `x & 0xFE` for a byte/char-typed x into a one-instruction
`movs r0,#0xFE; and`, but the retail build emits `movs r0,#2; negs r0,r0; and`
-- i.e. the mask was an `int` value `-2` flowing through a variable, not a
narrowed literal.  A `s32 m = -2;` local reproduces that (see sub_0806EE48).

This finds every `& 0xNN` in a seed where the mask is `~mask_of_one_bit`
(0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F and their wider forms) and
tries the `s32` local form under both compilers.

usage: mask_sweep.py [fn ...]
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from opcode_stubs import file_kind  # noqa: E402

CMP = re.compile(r"^\s*/\*\s*match-compiler:")
MASK_RE = re.compile(r"&\s*(0x[0-9A-Fa-f]+)\b")


def clear_masks(src: str) -> list[int]:
    out = []
    for m in MASK_RE.finditer(src):
        v = int(m.group(1), 16)
        if 0 < v < 0xFFFFFFFF and (v & (v + 1)) == 0:
            continue  # v+1 power of two => v is a keep-low-bits mask, skip
        if v == 0 or (v & 1) == 0:
            continue
        if (v & (v + 1)) != 0:
            continue
        out.append(v)
    # keep only ~(1<<n) forms
    return out


def variants(src: str) -> dict[str, str]:
    out = {}
    for v in dict.fromkeys(clear_masks(src)):
        neg = v - 0x100 if v <= 0xFF else (v - 0x10000 if v <= 0xFFFF else -1)
        if neg >= 0:
            continue
        pat = re.compile(rf"&\s*0x{v:0{len(hex(v)) - 2}X}\b")
        idx = [0]
        def sub(m):
            idx[0] += 1
            name = f"clr{idx[0]}"
            return f"& {name}"
        new = pat.sub(sub, src)
        if new == src:
            continue
        decls = "\n".join(
            f"    s32 clr{i + 1} = {neg};" for i in range(idx[0])
        )
        new = re.sub(
            r"(sub_[0-9A-Fa-f]+\([^)]*\)\s*\{)",
            lambda m: m.group(1) + "\n" + decls,
            new,
            count=1,
        )
        out[f"mask{hex(v)}"] = new
    return out


def score(fn: str, text: str, compiler: str) -> str:
    if compiler == "old_agbcc":
        if not CMP.match(text):
            text = "/* match-compiler: old_agbcc */\n" + text
    else:
        text = "\n".join(l for l in text.splitlines() if not CMP.match(l)) + "\n"
    tmp = Path("/tmp/mask_sweep") / f"{fn}_{compiler}.c"
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
        for tag, text in variants(src).items():
            for comp in ("agbcc", "old_agbcc"):
                if score(fn, text, comp).startswith("MATCH"):
                    print(f"*** MATCH {fn} [{tag}/{comp}]", flush=True)
                    hits.append((fn, tag, comp))
                    Path(f"/tmp/mask_sweep/{fn}_{tag}_{comp}_MATCH.c").write_text(text)
    print("HITS:", hits)
    return 0


if __name__ == "__main__":
    sys.exit(main())
