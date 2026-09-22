# sub_0802BAD4 — WIP

| | |
|--|--|
| ROM | `0x0802BAD4` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0802BAD4.c` |
| Last `match_function.py` | 50/320
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts. The final candidate reached 50/320 bytes (15.6%, 264B); it reconstructs argument normalization, sentinel scan, signed-range checks, optional sub_0802C3DC/sub_0803DEC8 path, error callback, record writes, and 0x80-entry search. Remaining mismatch is high-register/stack allocation and repeated main-work table address formation.

## Current state

Two semantic attempts. The final candidate reached 50/320 bytes (15.6%, 264B); it reconstructs argument normalization, sentinel scan, signed-range checks, optional sub_0802C3DC/sub_0803DEC8 path, error callback, record writes, and 0x80-entry search. Remaining mismatch is high-register/stack allocation and repeated main-work table address formation.

## Next

Preserve the 0xC-byte frame and exact normalized argument spills. Then force target registers: r7 must remain the 0x03000198 location, r3 the 0x1694 offset saved at sp+8 across sub_0802C3DC, r2 the current 4-byte slot, r5 the index offset, and r0 the table base. Reproduce repeated reloads of main_loc + offset for each byte store.
