# sub_0806E7BC — WIP

| | |
|--|--|
| ROM | `0x0806E7BC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0806E7BC.c` |
| Last `match_function.py` | 42/152
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: size_mismatch 42/152 (27.6%), compiled 148B vs retail 152B; attempted as line-segment intersection test (2D cross-product sign comparison, 8 s32 params ax,ay,bx,by,cx,cy,dx,dy) returning 0/1/2; logic direction plausible (first 8 bytes match: prologue) but overall structure/expression grouping doesn't match agbcc's register scheduling - needs more careful param/expr-order derivation from raw asm (subs order matters: check if retail computes abx=ax-bx or bx-ax first, etc)

## Current state

size_mismatch 42/152 (27.6%), compiled 148B vs retail 152B; attempted as line-segment intersection test (2D cross-product sign comparison, 8 s32 params ax,ay,bx,by,cx,cy,dx,dy) returning 0/1/2; logic direction plausible (first 8 bytes match: prologue) but overall structure/expression grouping doesn't match agbcc's register scheduling - needs more careful param/expr-order derivation from raw asm (subs order matters: check if retail computes abx=ax-bx or bx-ax first, etc)

## Next

re-derive param roles more carefully from asm (r12=a0 orig, r6=a1, r5=a2, r4=a3; stack args sp0x18/1C/20/24) - do NOT assume signature guessed here is correct; trace each subs/muls instruction to exact source expr before writing C
