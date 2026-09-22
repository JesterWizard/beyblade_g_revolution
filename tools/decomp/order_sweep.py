#!/usr/bin/env python3
"""Sweep top-level statement orders of a parked WIP seed.

Many agbcc/old_agbcc near-misses are pure scheduling: the same set of
independent loads/stores is emitted in a different order, because the compiler
hoists/sinks based on source statement order.  This tries adjacent swaps,
rotations, reversal and a few seeded shuffles of the function's top-level
statements, scoring each under both agbcc and old_agbcc.

usage: order_sweep.py <fn> <seed.c> [max_variants]
"""
from __future__ import annotations

import random
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match_function as mf  # noqa: E402

CMP = re.compile(r"^\s*/\*\s*match-compiler:")


def body_span(src: str) -> tuple[int, int] | None:
    m = re.search(r"^[A-Za-z_][A-Za-z0-9_ \t\*]*sub_[0-9A-Fa-f]+\s*\([^;{]*\)\s*\{", src, re.M)
    if not m:
        return None
    start = src.index("{", m.start()) + 1
    depth = 1
    i = start
    while i < len(src) and depth:
        c = src[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return start, i
        i += 1
    return None


def split_top(body: str) -> list[str]:
    parts, depth, cur = [], 0, ""
    for c in body:
        cur += c
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        elif c == ";" and depth == 0:
            parts.append(cur)
            cur = ""
    if cur.strip():
        parts.append(cur)
    return parts


def render(src: str, span: tuple[int, int], stmts: list[str]) -> str:
    s, e = span
    return src[:s] + "".join(stmts) + src[e:]


def variants(stmts: list[str], budget: int, seed: int = 7) -> list[tuple[str, list[str]]]:
    if len(stmts) < 2:
        return []
    out: list[tuple[str, list[str]]] = []
    n = len(stmts)
    for i in range(n - 1):
        v = list(stmts)
        v[i], v[i + 1] = v[i + 1], v[i]
        out.append((f"swap{i}", v))
    for k in range(1, n):
        out.append((f"rot{k}", stmts[k:] + stmts[:k]))
    out.append(("rev", stmts[::-1]))
    rnd = random.Random(seed)
    for j in range(12):
        v = list(stmts)
        rnd.shuffle(v)
        out.append((f"shuf{j}", v))
    return out[:budget]


def score(fn: str, text: str, compiler: str) -> tuple[str, str]:
    if compiler == "old_agbcc":
        if not CMP.match(text):
            text = "/* match-compiler: old_agbcc */\n" + text
    else:
        text = "\n".join(l for l in text.splitlines() if not CMP.match(l)) + "\n"
    tmp = Path("/tmp/order_sweep") / f"{fn}_{compiler}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_text(text)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True,
    )
    out = (r.stdout + r.stderr).strip().splitlines()
    return (out[0] if out else "?"), (out[1] if len(out) > 1 else "")


def main() -> int:
    fn, seed_path = sys.argv[1], Path(sys.argv[2])
    budget = int(sys.argv[3]) if len(sys.argv) > 3 else 24
    src = seed_path.read_text()
    span = body_span(src)
    if not span:
        print("could not locate function body")
        return 1
    stmts = split_top(src[span[0]:span[1]])
    print(f"{fn}: {len(stmts)} top-level statements")
    hits = []
    for tag, v in variants(stmts, budget):
        for comp in ("agbcc", "old_agbcc"):
            first, second = score(fn, render(src, span, v), comp)
            if first.startswith("MATCH"):
                print(f"*** MATCH {fn} [{tag}/{comp}]", flush=True)
                hits.append((tag, comp))
                Path(f"/tmp/order_sweep_{fn}_{tag}_{comp}.c").write_text(render(src, span, v))
            elif "same_size" in second:
                pct = re.search(r"(\d+)/(\d+) bytes", second)
                print(f"    {tag}/{comp} {pct.group(0) if pct else second}")
    print("HITS:", hits)
    return 0


if __name__ == "__main__":
    sys.exit(main())
