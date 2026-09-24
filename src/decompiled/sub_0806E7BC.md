# sub_0806E7BC — MATCH

| | |
|--|--|
| ROM | `0x0806E7BC` |
| `src/matched` | semantic C |
| Seed | `src/decompiled/sub_0806E7BC.c` |
| Last `match_function.py` | MATCH |

## Role

2D segment orientation: two cross products per pair, return 0 (no proper intersection), 1, or 2.

## Process

- Symmetric opposite-sign checks were the wrong CFG (retail continues when the second cross is 0).
- Shared fail/success labels + `result = 2; if (cross1 >= 0) result = 1` reached 149/152.
- Remaining dest was r1 vs r0 on the second cross `subs`. Assigning that product to `result` (the return local) put it in r0.

## Current state

MATCH, integrated `src/matched/sub_0806E7BC.c`.
