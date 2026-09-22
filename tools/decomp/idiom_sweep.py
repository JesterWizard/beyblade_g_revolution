#!/usr/bin/env python3
"""Apply block-shaping idioms to parked seeds and re-score.

agbcc's branch threading and register allocation both react to basic-block
boundaries, which are *source-reachable* in C through statement structure.  A
same-size DIFF whose only delta is a branch target or a register destination is
often fixed by giving a statement its own block.

Transforms applied (each scored under both compilers):
  braces      -- add braces around every single-statement `if` body
  dowhile     -- wrap every single-statement `if` body in `do { ... } while (0);`
  dowhile1    -- wrap only the last single-statement `if` body
  elsewrap    -- turn `if (c) s;` into `if (c) { s; } else {}` (no, kept simple)
  assignlast  -- hoist the final `return EXPR;` into a temp
  unbrace     -- remove braces from single-statement if bodies

usage: idiom_sweep.py [fn ...]     (default: all unmatched seeds >= MIN_PCT)
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from opcode_stubs import file_kind  # noqa: E402

CMP = re.compile(r"^\s*/\*\s*match-compiler:")
MIN_PCT = 70.0

IF_RE = re.compile(r"(?m)^(\s*)if\s*\((?P<cond>[^\n]*?)\)\s*\n(?P<ind>\s*)(?P<stmt>[^\n{}]*;)\s*$")


def braces(src: str) -> str:
    def rep(m):
        return f"{m.group(1)}if ({m.group('cond')})\n{m.group('ind')}{{\n{m.group('ind')}    {m.group('stmt')}\n{m.group('ind')}}}"
    return IF_RE.sub(rep, src)


def dowhile(src: str, only_last: bool = False) -> str:
    matches = list(IF_RE.finditer(src))
    if not matches:
        return src
    if only_last:
        matches = matches[-1:]
    out = src
    for m in reversed(matches):
        rep = (
            f"{m.group(1)}if ({m.group('cond')})\n"
            f"{m.group('ind')}do {{ {m.group('stmt')} }} while (0);"
        )
        out = out[: m.start()] + rep + out[m.end():]
    return out


RET_RE = re.compile(r"(?m)^(\s*)return\s+(?P<expr>[^;]+);\s*$")


def assignlast(src: str) -> str:
    m = None
    for m in RET_RE.finditer(src):
        pass
    if not m:
        return src
    sig = re.search(r"(?m)^([A-Za-z_][A-Za-z0-9_ \t\*]*?)\b(sub_[0-9A-Fa-f]+)\s*\(", src)
    if not sig:
        return src
    ret = sig.group(1).strip()
    return (
        src[: m.start()] + f"{m.group(1)}__tail = {m.group('expr')};\n{m.group(1)}return __tail;" + src[m.end():]
    ).replace(sig.group(2) + "(", sig.group(2) + "(", 1)


TRANSFORMS = {
    "braces": braces,
    "dowhile": lambda s: dowhile(s, False),
    "dowhile1": lambda s: dowhile(s, True),
}


def score(fn: str, text: str, compiler: str) -> str:
    if compiler == "old_agbcc":
        if not CMP.match(text):
            text = "/* match-compiler: old_agbcc */\n" + text
    else:
        text = "\n".join(l for l in text.splitlines() if not CMP.match(l)) + "\n"
    tmp = Path("/tmp/idiom_sweep") / f"{fn}_{compiler}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_text(text)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True,
    )
    out = r.stdout.strip().splitlines()
    return out[0] if out else "?"


def targets(only: set[str]) -> list[str]:
    if only:
        return sorted(only)
    data = json.loads(
        subprocess.run(
            [sys.executable, "tools/decomp/function_scores.py", "--json"],
            capture_output=True, text=True,
        ).stdout
    )
    out = []
    for f in data["functions"]:
        if f["status"] == "matched" or f["pct"] < MIN_PCT:
            continue
        if not Path(f"src/decompiled/{f['name']}.c").exists():
            continue
        matched = Path(f"src/matched/{f['name']}.c")
        if matched.exists() and file_kind(matched) == "semantic":
            continue
        out.append(f["name"])
    return out


def main() -> int:
    fns = targets(set(sys.argv[1:]))
    hits = []
    for fn in fns:
        src = Path(f"src/decompiled/{fn}.c").read_text()
        base = {}
        for name, fn_t in TRANSFORMS.items():
            text = fn_t(src)
            if text == src:
                continue
            for comp in ("agbcc", "old_agbcc"):
                tag = score(fn, text, comp)
                if tag.startswith("MATCH"):
                    print(f"*** MATCH {fn} [{name}/{comp}]", flush=True)
                    hits.append((fn, name, comp))
                    Path(f"/tmp/idiom_sweep/{fn}_{name}_{comp}_MATCH.c").write_text(text)
    print("HITS:", hits)
    return 0


if __name__ == "__main__":
    sys.exit(main())
