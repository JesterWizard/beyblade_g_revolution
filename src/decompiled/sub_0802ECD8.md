# sub_0802ECD8 — WIP

| | |
|--|--|
| ROM | `0x0802ECD8` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0802ECD8.c` |
| Last `match_function.py` | 50/498
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: two attempts did not match; 50/498 bytes, final compiled 416B; logic mapped but fixed high-register pins removed the retail callee-save prologue

## Current state

two attempts did not match; 50/498 bytes, final compiled 416B; logic mapped but fixed high-register pins removed the retail callee-save prologue

## Next

restore natural prologue from first seed, then selectively anchor buffer/index/root location without fixed r8-r10 pins
