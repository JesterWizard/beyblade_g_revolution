# sub_0803E2AC — WIP

| | |
|--|--|
| ROM | `0x0803E2AC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0803E2AC.c` |
| Last `match_function.py` | 67/124 then 72/124
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts are same-size but differ in table literal/index scheduling: 67/124 direct seed, 72/124 with r3 base and r0/r1/r2 pins. RGB table classification logic is identified.

## Current state

Two semantic attempts are same-size but differ in table literal/index scheduling: 67/124 direct seed, 72/124 with r3 base and r0/r1/r2 pins. RGB table classification logic is identified.

## Next

Use a targeted permuter/source-order search to force retail's table1 literal load before the signed 0x1E index, then preserve table2/table3 RGB accumulation and threshold branches.
