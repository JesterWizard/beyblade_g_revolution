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
