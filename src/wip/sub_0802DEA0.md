# sub_0802DEA0 — WIP

| | |
|--|--|
| ROM | `0x0802DEA0` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0802DEA0.c` |
| Last `match_function.py` | 66/424
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: 66/424 bytes (15.6%), size mismatch (400 vs 424); correct algorithm fully derived (16 near-identical blocks: for each of struct Unk026C's linked-list fields unk0C..unk40, if non-null set the node's unk08/unk0C to a color constant (0xFFFFC000 for the first 6, 0xF800 for the rest); then free+null 7 of those same fields via sub_0806FE84; finally vsync, set unk48=0xFF, and OR 0xFFFF into gMainWorkPtr's unk1838/unk183A). Reused existing structs Unk026C/Unk705DC. agbcc's CSE merges the repeated 'gUnk_0300026C' pointer dereference across adjacent blocks (r1 cached, reused via a spare register) even when each block is written as a fresh 'p = gUnk_0300026C' assignment, since no intervening write invalidates it -- retail instead reloads fresh every single block

## Current state

66/424 bytes (15.6%), size mismatch (400 vs 424); correct algorithm fully derived (16 near-identical blocks: for each of struct Unk026C's linked-list fields unk0C..unk40, if non-null set the node's unk08/unk0C to a color constant (0xFFFFC000 for the first 6, 0xF800 for the rest); then free+null 7 of those same fields via sub_0806FE84; finally vsync, set unk48=0xFF, and OR 0xFFFF into gMainWorkPtr's unk1838/unk183A). Reused existing structs Unk026C/Unk705DC. agbcc's CSE merges the repeated 'gUnk_0300026C' pointer dereference across adjacent blocks (r1 cached, reused via a spare register) even when each block is written as a fresh 'p = gUnk_0300026C' assignment, since no intervening write invalidates it -- retail instead reloads fresh every single block

## Next

try inserting a genuinely-opaque side effect between blocks (unlikely to be legitimate semantic C), or accept this as CSE the compiler correctly performs and retail's source simply repeated the full expression per block in a way this agbcc snapshot doesn't reproduce; may need per-block dummy calls or accept as permanently DIFF
