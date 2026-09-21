#!/usr/bin/env python3
"""Test C variants for a function.

usage: test_variants.py <function> <template.c> <variants.txt>
The template must contain the literal marker @@BODY@@ which is replaced by each
block in variants.txt (blocks separated by a line containing only '---').
"""
import sys, subprocess, os

fn, tpl_path, var_path = sys.argv[1], sys.argv[2], sys.argv[3]
tpl = open(tpl_path).read()
assert '@@BODY@@' in tpl, 'template needs @@BODY@@'
blocks = [b for b in open(var_path).read().split('\n---\n') if b.strip()]
outdir = '/tmp/v'
os.makedirs(outdir, exist_ok=True)
best = None
for i, blk in enumerate(blocks):
    src = tpl.replace('@@BODY@@', blk.rstrip('\n'))
    p = f'{outdir}/{fn}_{i}.c'
    open(p, 'w').write(src)
    r = subprocess.run(['python3', 'tools/decomp/match_function.py', fn, p],
                       capture_output=True, text=True)
    lines = r.stdout.strip().split('\n')
    tag = lines[0] if lines else '(no output)'
    if 'MATCH' in tag and 'DIFF' not in tag:
        print(f'*** SCORE 0 variant {i}: {tag}')
    elif len(lines) > 1:
        tag += ' ' + lines[1]
    print(f'[{i:>2}] {tag}')
    print('     ' + blk.replace('\n', '\n     ').rstrip())
print('template:', tpl_path)
