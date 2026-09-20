# sub_0804AC3C — WIP

| | |
|--|--|
| ROM | `0x0804AC3C` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0804AC3C.c` |
| Last `match_function.py` | 32/104 then 38/104
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two attempts: semantic seed 32/104 (96B), then r6/r5/r4 register-pinned data/first/second 38/104 (96B). Field offsets, transition calls, fixed-point positions, and cleanup are correct; remaining mismatch is retail's constant/coordinate register layout (r0/r1 and r4/r5) and an 8-byte size delta.

## Current state

Two attempts: semantic seed 32/104 (96B), then r6/r5/r4 register-pinned data/first/second 38/104 (96B). Field offsets, transition calls, fixed-point positions, and cleanup are correct; remaining mismatch is retail's constant/coordinate register layout (r0/r1 and r4/r5) and an 8-byte size delta.

## Next

Use a scoped r6 data pointer so it expires after sub_0804AAF0, make coordinate u16 to force retail lsr-to-r4 then adds r0, and preserve the direct fixed-point expression.
