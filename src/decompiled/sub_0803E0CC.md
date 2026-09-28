# sub_0803E0CC — WIP

| | |
|--|--|
| ROM | `0x0803E0CC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0803E0CC.c` |
| Last `match_function.py` | 56/296
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-28 — parked. Status: logic mapped (release all slots with unk23 == id); s8 unk1C |= 0xFF folds to strb -1, retail keeps ldrb/orr; loop.c hoists different constants

## Current state

logic mapped (release all slots with unk23 == id); s8 unk1C |= 0xFF folds to strb -1, retail keeps ldrb/orr; loop.c hoists different constants

## Next

unk1C likely a u8 view / bitfield here; other users need s8

## Process (final sweep)

- 2026-09-28 (final sweep): Data symbol gData_03000198 plus `unk1C |= (s8)0xFF` (keeps the ldrb/orr/strb instead of folding to strb -1): 56 -> 170/296. Still 4 bytes short: retail hoists the unk1C offset into r10, ours keeps it in r3 and caller-saves it to the stack. Next: Get the loop-invariant 0x8EC offset into a callee-saved register (r10); old_agbcc is required.
