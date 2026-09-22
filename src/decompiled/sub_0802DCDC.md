# sub_0802DCDC — WIP

| | |
|--|--|
| ROM | `0x0802DCDC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0802DCDC.c` |
| Last `match_function.py` | 100/452
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: size mismatch; 100/452 bytes, compiled 428 vs retail 452; direct semantic control flow mapped, but frame remains 0x1C vs retail 0x18 and high-register lifetimes differ

## Current state

size mismatch; 100/452 bytes, compiled 428 vs retail 452; direct semantic control flow mapped, but frame remains 0x1C vs retail 0x18 and high-register lifetimes differ

## Next

reduce spills to the retail 0x18 frame, preserve r8/r9/r10 and exact state-location reloads
