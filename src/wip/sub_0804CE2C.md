# sub_0804CE2C — WIP

| | |
|--|--|
| ROM | `0x0804CE2C` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0804CE2C.c` |
| Last `match_function.py` | 51/168 then 56/168
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: family seed 51/168 (176B), then r4/r6 explicit locals 56/168 (176B). Constants and call sequence are correct; agbcc still swaps the desired index/first-coordinate register allocation and retains an 8-byte size delta.

## Current state

Two semantic attempts: family seed 51/168 (176B), then r4/r6 explicit locals 56/168 (176B). Constants and call sequence are correct; agbcc still swaps the desired index/first-coordinate register allocation and retains an 8-byte size delta.

## Next

Use the established UI family permuter/source-order search for ordinary saved r4 input, r6 first coordinate, and saved r7 image; avoid the explicit local asm pins that reverse the prologue.
