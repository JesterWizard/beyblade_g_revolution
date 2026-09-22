# sub_0803DDD8 — WIP

| | |
|--|--|
| ROM | `0x0803DDD8` |
| Retail | 40 B: `tbl[a - 1]` (pointer table at `0x0807AEFC`) then `[row + gMainWorkPtr->unk1818]`, returned as a pointer |
| `src/matched` | `src/matched/sub_0803DDD8.c` — **MATCHED** (old_agbcc) |
| Seed | `src/decompiled/sub_0803DDD8.c` |
| Last `match_function.py` | 40/40 (`old_agbcc`) |
| Sibling / types | Twin of `sub_0803DDB0` (different table), `sub_0803DD88` (same family, 40-byte stride) |

## Role

Resolves the 40-byte record for slot `a - 1` and returns the pointer at the offset
selected by the live `unk1818` index.

## Process

- 2026-09-21 — **matched** with `/* match-compiler: old_agbcc */` plus the exact
  source shape: `u8 *tbl = <symbol>;` as a local, `u32 *row = (u32 *)(tbl + (a - 1) * 4);`
  (so `subs r0,#1` / `lsls #2` unfold instead of folding to `lsls #4`), and the
  dereference left inline as `*row` so old_agbcc hoists `ldr r1,=tbl` above the
  decrement like retail.
- Landing either `tbl` as a symbol reused twice, or `row` as a named dereference,
  re-colours the pool load and drops to 31–34/40.

## Current state

Matched and integrated; `make compare` OK.

## Next

Done. Pattern reused for `sub_0803DDB0` and (with a 40-byte stride) `sub_0803DD88`.
