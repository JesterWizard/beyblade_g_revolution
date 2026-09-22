# sub_0803DCFC — WIP

| | |
|--|--|
| ROM | `0x0803DCFC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0803DCFC.c` |
| Last `match_function.py` | 11/48
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: 11/48 same-size DIFF; index pinning and explicit goto preserved size, but retail uses a longer error-path layout and explicit shift/add sequence while agbcc still places the table return block differently

## Current state

11/48 same-size DIFF; index pinning and explicit goto preserved size, but retail uses a longer error-path layout and explicit shift/add sequence while agbcc still places the table return block differently

## Next

try a source layout that keeps the error call block before the valid table path while forcing  index and separate  offset; use the retail bls target shape
