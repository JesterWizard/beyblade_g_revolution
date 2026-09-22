#!/usr/bin/env python3
"""Test C variants for a function.

usage: test_variants.py <function> <template.c> <variants.txt> [compilers]
The template must contain the literal marker @@BODY@@ which is replaced by each
block in variants.txt (blocks separated by a line containing only '---').

Every variant is scored under BOTH agbcc and old_agbcc by default, because the
two compilers pick different registers for the same source (`match_function.py`
defaults to agbcc alone, which silently misses old_agbcc-only matches).
Pass e.g. `agbcc` or `old_agbcc` as the 4th argument to restrict.
"""
import sys, subprocess, os, re

CMP = re.compile(r"^\s*/\*\s*match-compiler:")


def restamp(src: str, compiler: str) -> str:
    src = "\n".join(l for l in src.splitlines() if not CMP.match(l))
    if compiler == "old_agbcc":
        src = "/* match-compiler: old_agbcc */\n" + src
    return src


def score(fn: str, src: str, variant_idx: int, compiler: str):
    p = f"/tmp/v/{fn}_{variant_idx}_{compiler}.c"
    open(p, "w").write(restamp(src, compiler))
    r = subprocess.run(["python3", "tools/decomp/match_function.py", fn, p],
                       capture_output=True, text=True)
    lines = r.stdout.strip().split("\n")
    return lines[0] if lines else "(no output)", (lines[1] if len(lines) > 1 else "")


fn, tpl_path, var_path = sys.argv[1], sys.argv[2], sys.argv[3]
compilers = [sys.argv[4]] if len(sys.argv) > 4 else ["agbcc", "old_agbcc"]
tpl = open(tpl_path).read()
assert '@@BODY@@' in tpl, 'template needs @@BODY@@'
blocks = [b for b in open(var_path).read().split('\n---\n') if b.strip()]
outdir = '/tmp/v'
os.makedirs(outdir, exist_ok=True)
best = None
for i, blk in enumerate(blocks):
    src = tpl.replace('@@BODY@@', blk.rstrip('\n'))
    for compiler in compilers:
        tag, second = score(fn, src, i, compiler)
        if 'MATCH' in tag and 'DIFF' not in tag:
            print(f'*** SCORE 0 variant {i} [{compiler}]: {tag}')
        elif second:
            tag += ' ' + second
        print(f'[{i:>2}/{compiler}] {tag}')
    print('     ' + blk.replace('\n', '\n     ').rstrip())
print('template:', tpl_path)
