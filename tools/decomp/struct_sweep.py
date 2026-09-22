#!/usr/bin/env python3
"""Sweep structural variants of every genuinely-unmatched parked WIP seed.

Variant "tail assign": `return EXPR;` -> `__tail = EXPR; return __tail;` with a
function-scope declaration. Keeps the returned value live one reference longer,
which changes agbcc's local-alloc priority split (see sub_0806B064).

Both agbcc and old_agbcc are scored for each variant.
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import file_kind  # noqa: E402

RET_RE = re.compile(r"^(\s*)return\s+(.+?);\s*$", re.M)
SIG_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_ \t\*]*?)\b(sub_[0-9A-Fa-f]+)\s*\(", re.M)
CMP = re.compile(r"^\s*/\*\s*match-compiler:")


def score(fn: str, text: str, compiler: str) -> tuple[str, str]:
    if compiler == "old_agbcc":
        if not CMP.match(text):
            text = "/* match-compiler: old_agbcc */\n" + text
    else:
        text = "\n".join(l for l in text.splitlines() if not CMP.match(l)) + "\n"
    tmp = Path("/tmp/struct_sweep") / f"{fn}_{compiler}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_text(text)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True,
    )
    out = r.stdout.strip().splitlines()
    return (out[0] if out else "?"), (out[1] if len(out) > 1 else "")


def tail_assign(src: str) -> str | None:
    m = SIG_RE.search(src)
    if not m:
        return None
    ret = m.group(1).strip()
    if not ret or ret.endswith(")"):
        return None
    last = None
    for mt in RET_RE.finditer(src):
        last = mt
    if not last:
        return None
    expr = last.group(2)
    if expr.startswith("__tail"):
        return None
    new = src[: last.start()] + f"    __tail = {expr};\n    return __tail;" + src[last.end():]
    # insert declaration right after the function's opening brace
    brace = new.find("{", m.end())
    if brace < 0:
        return None
    return new[: brace + 1] + f"\n    {ret} __tail;" + new[brace + 1 :]


def main() -> int:
    hits = []
    for p in sorted(Path("src/wip").glob("sub_*.c")):
        fn = p.stem
        matched = Path(f"src/matched/{fn}.c")
        if matched.exists() and file_kind(matched) == "semantic":
            continue
        src = p.read_text()
        variants = {}
        t = tail_assign(src)
        if t:
            variants["tail"] = t
        for tag, text in variants.items():
            for comp in ("agbcc", "old_agbcc"):
                first, second = score(fn, text, comp)
                if first.startswith("MATCH"):
                    print(f"*** MATCH {fn} [{tag}/{comp}]", flush=True)
                    hits.append((fn, tag, comp))
                    Path(f"/tmp/struct_sweep/{fn}_{tag}_{comp}_MATCH.c").write_text(text)
    print("HITS:", hits)
    return 0


if __name__ == "__main__":
    sys.exit(main())
