# sub_0804AAF0 — WIP

| | |
|--|--|
| ROM | `0x0804AAF0` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_0804AAF0.c` |
| Last `match_function.py` | 145/332 then 151/332
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: initial 145/332 (324B), then early current-global address ordering 151/332 (324B). All menu entry fields, allocator, resource lookups, draw calls, flags, decompression, and cleanup are mapped; remaining mismatch is compiler ordering/literal-pool/register shape around the 0x03000660/0x03000658 setup.

## Current state

Two semantic attempts: initial 145/332 (324B), then early current-global address ordering 151/332 (324B). All menu entry fields, allocator, resource lookups, draw calls, flags, decompression, and cleanup are mapped; remaining mismatch is compiler ordering/literal-pool/register shape around the 0x03000660/0x03000658 setup.

## Next

Restore the semantic seed and use targeted source-order/permuter work to force retail r4=0x03000660 before the signed index lookup, while retaining the resource call sequence and final reload.
