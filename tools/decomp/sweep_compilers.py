#!/usr/bin/env python3
"""Sweep every parked WIP seed and every readable-Thumb function through
match_function.py with both agbcc and old_agbcc; report any MATCH."""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
WIP = sorted(Path("src/wip").glob("sub_*.c"))
cmp_re = re.compile(r"^/\*\s*match-compiler:")


def score(fn, src_text, compiler):
    tmp = Path("/tmp/sweep") / f"{fn}_{compiler}.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    if compiler == "old_agbcc":
        if cmp_re.match(src_text.splitlines()[0] if src_text.splitlines() else ""):
            text = src_text
        else:
            text = "/* match-compiler: old_agbcc */\n" + src_text
    else:
        text = "\n".join(
            l for l in src_text.splitlines()
            if not cmp_re.match(l)
        ) + "\n"
    tmp.write_text(text)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True,
    )
    out = r.stdout.strip().splitlines()
    first = out[0] if out else "?"
    second = out[1] if len(out) > 1 else ""
    return first, second


if __name__ == "__main__":
    only = sys.argv[1:] or None
    hits = []
    for p in WIP:
        fn = p.stem
        if only and fn not in only:
            continue
        text = p.read_text()
        for comp in ("agbcc", "old_agbcc"):
            first, second = score(fn, text, comp)
            if first.startswith("MATCH"):
                hits.append((fn, comp))
                print(f"*** MATCH {fn} [{comp}]", flush=True)
            elif "same_size" in second or "same-size" in second:
                print(f"    {fn} [{comp}] {first} {second}", flush=True)
    print("HITS:", hits)
