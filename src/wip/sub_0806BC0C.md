# sub_0806BC0C — WIP

| | |
|--|--|
| ROM | `0x0806BC0C` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0806BC0C.c` |
| Last `match_function.py` | 46/116 then 43/116
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: direct bounded index loop 46/116 (104B), then an explicit fixed-point loop shape 43/116 (112B). The state/source layout and cap callback match; the remaining register issue is keeping the capped count in r4 so retail emits movs r4,#0x40, then transferring count<<16 into r6. The final scratch revision applies that shape but was not retried under the two-attempt limit.

## Current state

Two semantic attempts: direct bounded index loop 46/116 (104B), then an explicit fixed-point loop shape 43/116 (112B). The state/source layout and cap callback match; the remaining register issue is keeping the capped count in r4 so retail emits movs r4,#0x40, then transferring count<<16 into r6. The final scratch revision applies that shape but was not retried under the two-attempt limit.

## Next

Compile the final revision with current/count pinned to r4 and limit pinned to r6. Preserve the source count halfword load, cap callback, and fixed-point loop; verify the post-loop +0x114/+0x10/+0x118 stores.
