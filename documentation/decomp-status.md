# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

| Metric | Value |
|--------|-------|
| Non-matching asm | 633 |
| Matching asm (linked) | 11 |
| `src/*.c` files | 1 |
| `pct_asm_matched` | 1.7% |

## Matched + linked (ROM peel)

- [x] `sub_08033A94` — `ldrb` load → `src/stubs.c`
- [x] `sub_08062098` — field load at +0x18 → `src/stubs.c`
- [x] `sub_08062A14` — literal pool load (`asm/matchings`)
- [x] `sub_08067A9C` — empty return stub → `src/stubs.c`
- [x] `sub_0806EEC4` — empty return stub → `src/stubs.c`
- [x] `sub_080674A0` — `swi #6` stub
- [x] `sub_080674A4` — `swi #6` + `mov r0, r1`
- [x] `sub_080674AC` — `swi #17` stub
- [x] `sub_080674B0` — `swi #8` stub
- [x] `sub_080674B4` — `swi #5` stub
- [x] `sub_08074144` — `mov pc, lr` stub

## Tooling added this session

- `scripts/decomp/gen_rom_layout.py` — baserom peel + fixed-VMA linker fragment
- `scripts/decomp/integrate_match.py` — land a match into `asm/matchings/` + regenerate layout
- `build/matched.json` — manifest of linked functions
- `asm/rom_layout.ld` — generated; included from `ld_script.ld`

## Batch log

### 2026-09-17 — linker integration + second batch

- ROM peel wired: 11 functions linked at retail addresses
- `make compare`: **OK**
- Triage skips `asm/matchings/`; m2c failures no longer fed to agbcc

### 2026-09-17 — bootstrap + first Cursor batch

- Fixed `scripts/generate_asm.py` split (trim gap `.byte` between functions)
- First 4 functions verified via `match_function.py` + `src/stubs.c`

## Next

- Decompile `sub_0802B90C` and other literal-pool helpers (m2c needs asm preprocessor)
- Replace asm matchings with C as `match_function.py` passes
- Run `scripts/decomp/cursor_batch.sh 10` on fresh triage list

## Blockers

- None for matching build (`make compare` green with 11 peeled functions)
