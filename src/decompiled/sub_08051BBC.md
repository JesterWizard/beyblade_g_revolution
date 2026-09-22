# sub_08051BBC — WIP

| | |
|--|--|
| ROM | `0x08051BBC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_08051BBC.c` |
| Last `match_function.py` | 24/124 then 26/124
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: direct field/volatile loop 24/124 (144B), then pinned main-location/BLDY anchors 26/124 (156B). Fade counters and register writes are semantically correct, but the retail uses a compact offset-register layout and the typed pointer anchors add code.

## Current state

Two semantic attempts: direct field/volatile loop 24/124 (144B), then pinned main-location/BLDY anchors 26/124 (156B). Fade counters and register writes are semantically correct, but the retail uses a compact offset-register layout and the typed pointer anchors add code.

## Next

Restore direct semantic fields and use targeted source-order/permuter work for retail r5=main-location, r4=0x17F0 offset, r6=BLDY; preserve loop writes and callback order.
