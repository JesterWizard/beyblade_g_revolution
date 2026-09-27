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

- 2026-09-27 — rewritten in the sibling `sub_0802D8DC` style → 416/452 same-size. Keys:
  second block re-reads `main = gMainWorkPtr` before copying unk1838/183A; the palette
  argument goes through a `u32 *palette = gData_080BB8C0` local (retail loads the address
  before the call). Left: `main`/`p` register swap (retail main=r5, p=r3). Permuter 900s:
  best 155, only via a junk self-assignment.

## Process (sweep 9)

- 2026-09-27 (sweep 9): permuter 900 s, 200 -> 95 (437/452 same size) only via non-semantic edits (array local, split `unk1808` store). Saved: src/decompiled/permuter/sub_0802DCDC.c.

## Current state

size mismatch; 100/452 bytes, compiled 428 vs retail 452; direct semantic control flow mapped, but frame remains 0x1C vs retail 0x18 and high-register lifetimes differ

## Next

Find what makes `main` the callee-saved (r5) pseudo in the first block.
