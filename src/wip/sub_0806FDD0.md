# sub_0806FDD0 — WIP

| | |
|--|--|
| ROM | `0x0806FDD0` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0806FDD0.c` |
| Last `match_function.py` | 8/128 then 21/128
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: sorted-list insertion model 8/128 (120B), then corrected u16 key ABI and literal pointer lifetimes reached 21/128 (120B). The body is structurally exact, but retail saves r7 (f0b5) while agbcc emits 70b5 despite keeping the free-list address in r7 across calls; this shifts literal-pool offsets and leaves the match short.

## Current state

Two semantic attempts: sorted-list insertion model 8/128 (120B), then corrected u16 key ABI and literal pointer lifetimes reached 21/128 (120B). The body is structurally exact, but retail saves r7 (f0b5) while agbcc emits 70b5 despite keeping the free-list address in r7 across calls; this shifts literal-pool offsets and leaves the match short.

## Next

Force a normal callee-saved local live across sub_0806FDB4/sub_0806F8C4 so agbcc emits the r7 save/restore, while retaining key as u16, free-list address r7, head address r5, and node r4. Then verify the sorted predecessor/successor insertion and counter decrement.
