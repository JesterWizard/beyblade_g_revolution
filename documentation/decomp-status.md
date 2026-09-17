# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

| Metric | Value |
|--------|-------|
| Non-matching asm | 633 |
| Matching asm | 0 |
| `src/*.c` files | 1 (4 functions verified, not yet linked) |
| Verified matches (scratch) | 4 |

## Matched functions

- [x] `sub_08067A9C` → `src/stubs.c` (empty return stub)
- [x] `sub_0806EEC4` → `src/stubs.c` (empty return stub)
- [x] `sub_08033A94` → `src/stubs.c` (`ldrb` load)
- [x] `sub_08062098` → `src/stubs.c` (struct field load at +0x18)

## Pending / failed

- [ ] `sub_08074144` — `mov pc, lr` stub; agbcc emits `bx lr` (needs asm or permuter)
- [ ] `sub_0802B90C` — literal-pool load; m2c needs Luvdis asm cleanup

## Batch log

### 2026-09-17 — bootstrap + first Cursor batch

- Fixed `scripts/generate_asm.py` split (trim gap `.byte` between functions)
- `make compare`: OK
- `scripts/decomp/cursor_batch.sh 5`: 4/5 verified via `match_function.py`
- Blocker: full linker integration (shrink `asm/rom.s`, `ld_script.ld`) not wired yet — matched C lives in `src/` but is not linked

## Blockers

- Linker peel / LynJump integration needed before matched `src/` affects `make compare`
- Mizuchi optional (needs npm + `ANTHROPIC_API_KEY`); primary path is `scripts/decomp/cursor_batch.sh`
