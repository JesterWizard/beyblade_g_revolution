# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

<!-- decomp-progress:start -->
| Metric | Value |
|--------|-------|
| Linked in ROM | **633/633** (100% peeled) |
| **Decompiled C (functions)** | **129/633 (20.4%)** |
| **Decompiled C (bytes)** | **3,742/90,272 (4.1%)** |
| Not opcode (C + readable Thumb) | 279/633 (44.1% fn, 45.6% bytes) |
| Readable Thumb | 150/633 (23.7%) |
| Opcode `.byte` embeds | 354/633 (55.9%) |
| `src/matched/*.c` | 633/633 |
| Phase | **3b in progress — replace opcode stubs with semantic C / readable Thumb** |
| Battle semantic C | 12/160 (7.5% fn, 1.5% bytes) |
| Counter | [`decomp-progress.svg`](decomp-progress.svg) · [`decomp-progress.json`](decomp-progress.json) |
<!-- decomp-progress:end -->

## Batch log

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08031094` (clamp via `31124` then `346A8`), `sub_0802E1B4` (`42BE8`/`42BB0`/`42B78` then `31124`)
- Grew `Unk346A8` (`unk04`), `Unk310F0Inner2` (`unk21`); `sub_080674B0` now returns the SWI 8 result; `sub_08042BE8`/`42BB0`/`42B78` take/return word-width values
- Near-miss: `sub_08041858` (pool-fold `0x504`), `sub_08054454` (zero vs addr regs), `sub_080360BC` (r8/r9), `sub_08067F3C` (extra r8)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+11)

- Semantic C: `sub_0802E18C` (div/mod tens), `sub_08070AD4`/`70DF4` (`7069C` then draw), `sub_08041980` (free 32 `Unk68574` slots), `sub_080686B4` (callback or copy 3 words), `sub_0806F174` (store + optional `6F05C`/`73C4C`), `sub_080310F0` (clamp via `31124`), `sub_08043ADC` (stride-`0xDC` free + `6A434`), `sub_08033D90` (rng index + `35878`), `sub_0802E210` (`42E78`/`42BE8`), `sub_0803413C` (Unk33F30 setup)
- Grew `Unk33F30` (front fields, `unk1C` inner), `Unk070C` (`unk00[13]`), `Unk0798` (`unk5D`/`unk94`), `Unk312EC` (`unk08` as byte); `sub_080674A4` now takes dividend/divisor
- Near-miss: `sub_08033C1C` (pool-fold `&unk0C` → `0x0300038C`), `sub_08062C80` (extra 4B), `sub_080408C4` (epilogue / extra sxt), `sub_08060D28`/`61308` (pool order)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08061BAC` (free 4 stride-8 slots at `0x03000770`, clear `0x03000794`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08043C28` (free four pointers at `0x030005F0`), `sub_08068808` (free `unkB8`/`unk7C`, clear `unk74`–`unk7C`)
- Grew `Unk68574` (`unk74`/`unk78`/`unk7C`/`unkB8`); added `Unk05F0`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_08062044` (free `unk00` then clear `unk0C`), `sub_0807069C`/`703FC`, `sub_08054558` (nested `Unk7069C` at +0x34), `sub_0806EBF8` (8-word stack pair), `sub_08040618` (pop `Unk047C` table)
- Grew `Unk7069C` (`unk0A`), `Unk047C` (`unk808`); added `Unk070C`/`Unk703FC`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+16)

- Semantic C: `sub_08033F48`/`3403C`/`34360`/`33E3C` (Unk33F30 init/tick), `sub_0803484C`, `sub_08040530`, `sub_0802EECC`/`2FD80` (VBlank + `_08073C40`), `sub_080312EC`, `sub_08034FBC`, `sub_08045AA8`, `sub_08060254`, `sub_080608D4`, `sub_08067634`, `sub_08070C98`, `sub_08031124`
- Grew `Unk33F30`/`Unk68574`/`Unk0798`/`Unk047C`/`Unk026C`/`Unk0748`; promoted `gUnk_0300026C`; `sub_080674A0` now takes dividend/divisor
- Near-miss: `sub_080447CC` (ld r1 vs r0), `sub_08033C1C`/`615EC` (pool fold / extra lr), `sub_080679A4`/`679C0`/`5DA70` (pool order)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_080405E8` (append to `Unk047C` pointer table), `sub_0805D1AC` (nested `sub_08068418` / `sub_08067CE8`), `sub_08062238` (free `unk08` then `sub_08062684`)
- Grew `Unk047C` (`unk00[0x200]`, `unk80C`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_0804BE80`/`4CA30`/`4D58C`, `sub_0803A1E4` (VBlank + `_08073C40`), `sub_08062960`, `sub_080611F0`, `sub_08070678`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+18)

- Semantic C: `sub_08048D0C`/`50864`/`538A0`/`54108`/`56380`/`56AF0` (VBlank + `sub_08061BE8` wrappers), `sub_08035238`, `sub_08071FC8`, `sub_08068558`, `sub_08034FF8`/`34FDC`, `sub_0807339C`, `sub_08073184`, `sub_080400D4`, `sub_080604A4`/`60798`, `sub_080626B8`, `sub_08045A84`
- Grew `Unk71F84` (`unk10`), `Unk68574` (`unkA8`–`unkAE`); added `Unk34FF8`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_080674A4` (SWI 6 remainder), `sub_080447B4` (NULL-terminated `sub_08059AE0` list), `sub_080346C0` (store 4 fields if `*a`)
- Grew `Unk312EC` / `Unk68014`; extra-`push {lr}` still blocks `sub_08061E40`/`62728`/`6AC68`/`69F00`/`6BE08`/`717F0`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+10)

- Semantic C: `sub_08071FAC`, `sub_080312D8`, `sub_080400C0`, `sub_08061784`/`B4`, `sub_08061A98`/`AA8`, `sub_08067890`, `sub_08069C14`, `sub_08068014`
- Promoted RAM: `gUnk_03000180` (`Unk0180`), `gUnk_0300047C` (`Unk047C *`), `gUnk_03000798` (`Unk0798 *` with `unk98`/`unk9C`/`unkA0` packing)
- Near-miss: `sub_080312EC` (`ldrb r1` vs `r0`), `sub_080473E4` (CSE of `0x03000634`/`63C`), `sub_0807069C` (`strh` +2 vs +4), `sub_08062A1C`/`66434`/`66440` (folded `base+off` pool)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+14)

- Semantic C: `sub_080603E0`, `sub_08043BDC`, `sub_08060428`/`38`/`48`/`58`, `sub_08060394`, `sub_080602C0`, `sub_08033F24`, `sub_08034414`, `sub_08032DB8`, `sub_080686D8`, `sub_08071F84`, `sub_08071F98`
- Grew `MainWork` (`unk16C8`/`unk16E0`/`unk16E4`/`unk181A`/`unk181F`) and `BattleWork` (`unk1FAC`/`unk201C`/`unk2088`)
- Tooling: decomp scripts import `tools/decomp/` (leftover `scripts/decomp` Path joins)
- Near-miss: `sub_08043B90` (extra `movs r0,#0`), `sub_08033530` (reg alloc), `sub_0804495C` (leaf prologue)
- `make compare`: **OK**

### 2026-09-17 — Phase 3b battle: reloc + readable Thumb + semantic C (+8)

- `match_function.py`: Thumb `R_ARM_THM_CALL` reloc patcher also covers `_080…` local labels (not only `sub_*`)
- Remaining **36** battle `.byte` stubs → readable Thumb (`readable_asm_batch.py`); **0 battle opcode left**
- Semantic C: `sub_080433F4`, `sub_0802E1EC`, `sub_0802BA4C`, `sub_08044EE8`, `sub_0803E440`, `sub_0806013C`, `sub_08060220`, `sub_080628B4`
- Grew `MainWork`: `unk1688`/`unk1694`/`unk1710[]`/`unk177C`/`unk1780`/`unk1798`/`unk179C`/`unk1819`/`unk1861[]`
- Near-miss (keep readable Thumb): `sub_080428C4`/`sub_080475C4`/`sub_080475F4`/`sub_0806FF28` (extra `push {lr}`), `sub_0806FEFC` (CSE `tail = head+0x10`), table family (pool order / `idx-1` fold)
- `make compare`: **OK**

### 2026-09-17 — C convention: struct members (aw2bhr style)

- Added `include/unknown-types.h` / `unknown-functions.h`; growing structs with `filler_XX` + `unkXX`
- Typed RAM macros: `gMainWorkPtr`, `gBattleWork` in `ram_map.h`
- Converted existing semantic C from offset-casts to `a->unkXX` / `g->unkXX`
- `c_patterns.py` now emits member stores; SWI r2=0 uses a register asm local, not `asm volatile`
- `make compare`: **OK**

### 2026-09-17 — decomp-permuter + battle readable Thumb (+122)

- Wired [decomp-permuter](https://github.com/simonlindholm/decomp-permuter): `permuter_settings.toml`, `tools/decomp/permuter/`
- `match_function.py` now applies `R_ARM_THM_CALL` so `bl sub_*` matches retail encodings
- Battle `.byte` stubs → readable Thumb (`--kind asm`): **122 converted**, 36 still opcode (BL to non-`sub_*`)
- Permuter on `sub_08072F94`: base score 50 (agbcc always deref-first); 11k+ iters, no score-0 — keep as readable Thumb until C matches
- `make compare`: **OK**

### 2026-09-17 — Phase 3b semantic batch (+15)

- `c_patterns.py`: field init, offset stores, three-u16/u32 patterns
- Converted: `sub_080338E4`, `sub_080346A8`, `sub_080358CC`, `sub_08035878`, `sub_08068574`, `sub_0806BB38`, `sub_0806B5B8`, `sub_0803EDC8`, `sub_08036190`, …
- `make compare`: **OK**

### 2026-09-17 — Phase 3b semantic C bootstrap

- Goal: replace `__attribute__((naked))` + `.byte` opcode embeds with readable, byte-matched C
- Added `tools/decomp/semantic_convert_batch.py`, `m2c_asm.py`, `opcode_stubs.py`
- `c_patterns.guess_c()` no longer falls back to opcode embed (use `guess_opcode_embed()` explicitly)
- First semantic replacement: `sub_08068584` (two `strh` field stores)
- Run: `tools/decomp/semantic_convert_batch.sh 30 --pool-free-only` for easy wins
- Pool/literal-pool functions (e.g. `sub_08061610`) need m2c + hand refine or permuter

### 2026-09-17 — Phase 3 complete (633/633 C placeholders)

- `c_patterns.py`: semantic patterns + `_naked_retail()` fallback (embeds exact retail opcodes)
- Batched conversion: trivial/IWRAM accessors → naked bytes ≤48B → ≤128B → ≤256B → remainder (≤1552B)
- `triage_functions.py` json fix; `c_convert_batch.sh` stdout fix
- `ram_map_pass.sh` run mid-session
- `make compare`: **OK**; `check_shiftable.py`: 633/633 linked, 980 fixed-VMA sections remain (Phase 5)

**Note:** Many functions use `__attribute__((naked))` + `.byte` opcode embedding where agbcc cannot reproduce literal-pool/ordering. Semantic C exists for early batches (battle, IWRAM loaders, swi stubs). Phase 4 should replace `sub_*` names; Phase 5 can migrate to shiftable layout.

### 2026-09-17 — Phase 3 C batch (+15 naked retail bytes)

- `c_patterns.py`: fallback embeds exact retail opcodes for functions ≤12B
- Converted 14 via batch + `sub_080674A4` (swi + adds r0,r1)
- `make compare`: **OK**

### 2026-09-17 — Phase 3 C batch (+9 patterns)

- Fixed `triage_functions.py` (`json` shadowing bug)
- Extended `c_patterns.py`: naked return, swi+r2 prep, IWRAM pool loaders, stack shim
- Fixed `c_convert_batch.sh` stdout capture from `integrate_c.py`
- New C: `sub_0802B90C`, `sub_080429C0`, `sub_08043974`, `sub_08062A14`, `sub_08066390`, `sub_080674B4`, `sub_08071808`, `sub_08074144`, `sub_08067B98`
- `make compare`: **OK**

### 2026-09-17 — Phase 3 battle C batch (+1)

- `sub_080314FC` → `src/matched/sub_080314FC.c` (battle work field @ +0x118)
- `tools/decomp/battle_convert_batch.sh` added
- `make compare`: **OK**

### Asm-only (documented blockers)

agbcc cannot reproduce these as C (literal-pool / instruction scheduling). They now have **readable Thumb** in `src/matched/` instead of `.byte` blobs. Permuter target when C is close.

| Function | Reason |
|----------|--------|
| `sub_08072F94` | agbcc loads `gBtlLookupPtr` before the addend (permuter score 50) |
| `sub_0803DD60` family | main-work table via `+0x1818`; same-size pool/reg order (`idx-1` folds into `base-4`) |
| `sub_08034894` | agbcc extra prologue / pool ordering |
| `sub_0806FEFC` | Freelist pop; agbcc CSEs `gBtlObjListTail` as `head+0x10` |
| `sub_0806FF28` / `sub_080428C4` / `sub_080475C4` / `sub_080475F4` | C adds `push {lr}` on a retail leaf |
| `sub_0802C62C` | Same size; count/`want` register swap (`r3` vs `r4`) |
| `sub_0806A6F8` | Large input hub; C not attempted |

### 2026-09-17 — Phase 3 battle subsystem bootstrap

- `include/battle.h`, `docs/battle.md`, `tools/decomp/battle_scan.py`
- Named battle IWRAM: `gBtlInputMask`, `gBtlKeysHeld`, object table, key queue, …
- First battle C: `sub_080628E4` (main-work arena write @ `+0x1800`)
- `make compare`: **OK**

### 2026-09-17 — Phase 3 C batch (trivial patterns)

- Fixed `match_function.py` (retail baserom byte compare; was broken objdump filter)
- Added `integrate_c.py`, `c_patterns.py`, `c_convert_batch.sh`
- Converted **9** trivial functions → `src/matched/*.c` (`make compare`: **OK**)
- Patterns: empty return, `ldrb` load, `ldr` + offset, `strb` field set, `swi` stubs

### 2026-09-17 — Phase 2 RAM map pass

- Rescanned `baserom.gba` literal pools: 250 IWRAM refs, high-water `0x03005694`
- Removed sigma_star_saga placeholder `KNOWN_IWRAM`; known symbols now parsed from `asm/ram_map_*.s`
- Emitted `asm/ram_map_iwram_pool.inc` (247 `gUnk_*`), `include/ram_map_pool.h`, `docs/ram-map.md`
- Promoted: `gMainWorkPtr`, `gBattleWork`, `gBattlerArena`
- Added `tools/decomp/ram_map_pass.sh`; `make compare`: **OK**

### 2026-09-17 — batch 3 (20 functions)

Integrated 20 asm-verified functions including literal-pool loaders (`sub_0802B90C`, `sub_080429C0`, …), IWRAM accessors, and field setters. `make compare`: **OK**.

### 2026-09-17 — linker integration + batch 2

11 functions linked via ROM peel tooling.

### 2026-09-17 — bootstrap + batch 1

First 4 functions + `src/stubs.c`.

## Tooling

| Script | Purpose |
|--------|---------|
| `tools/decomp/cursor_batch.sh` | Triage + m2c seeds |
| `tools/decomp/integrate_match.py` | Link match into ROM peel |
| `tools/decomp/match_function.py` | Verify scratch C vs asm (now runs CPP; patches Thumb BL relocs) |
| `tools/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |
| `tools/decomp/permuter/` | decomp-permuter wrappers (agbcc pool/order search) |

## Next

- **Phase 3b:** More battle semantic C (`sub_080428C4` family, freelist, table lookups via permuter); types on `gUnk_03000268` / `gUnk_03000630`
- **Phase 4:** Batch `[renames]` in `beyblade_g_revolution.toml` (battle subsystem first)
- **Phase 5:** Shiftable ROM migration (`check_shiftable.py` gates: 633/633 ✓, fixed-VMA sections ✗)

## Blockers

- None (`make compare` OK with all 633 functions linked)

### 2026-09-17 — match_batch (+10, 41/633 linked)
- Functions: `sub_080473E4`, `sub_08061BDC`, `sub_08062634`, `sub_08062A1C`, `sub_0806644C`, `sub_08068584`, `sub_08072F94`, `sub_0802B8BC`, `sub_0803EDC8`, `sub_080400C0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 51/633 linked)
- Functions: `sub_080628E4`, `sub_08067890`, `sub_080314FC`, `sub_0803EDF0`, `sub_08068574`, `sub_0806BB38`, `sub_0802D598`, `sub_0802D8C4`, `sub_08062728`, `sub_0806639C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 61/633 linked)
- Functions: `sub_080717F0`, `sub_08033958`, `sub_08061610`, `sub_08061E40`, `sub_08062684`, `sub_0806DEF4`, `sub_0806AC68`, `sub_080705A4`, `sub_080705DC`, `sub_08033F30`
- make compare: OK

### 2026-09-17 — match_batch (+10, 71/633 linked)
- Functions: `sub_08036190`, `sub_08042E78`, `sub_08068884`, `sub_08069F00`, `sub_0806A954`, `sub_0806BE08`, `sub_080346C0`, `sub_0803DD60`, `sub_0803EBB0`, `sub_0803EC34`
- make compare: OK

### 2026-09-17 — match_batch (+10, 81/633 linked)
- Functions: `sub_08033F24`, `sub_08034414`, `sub_08032DB8`, `sub_080686D8`, `sub_080602C0`, `sub_08060394`, `sub_08060428`, `sub_08060438`, `sub_08060448`, `sub_08060458`
- make compare: OK

### 2026-09-17 — match_batch (+10, 91/633 linked)
- Functions: `sub_080312EC`, `sub_08060254`, `sub_08067634`, `sub_080679C0`, `sub_08069C14`, `sub_0807069C`, `sub_08071F84`, `sub_08071F98`, `sub_08034FDC`, `sub_0803ECB8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 101/633 linked)
- Functions: `sub_08040530`, `sub_08042B00`, `sub_080447B4`, `sub_080679A4`, `sub_0806BDA8`, `sub_08031294`, `sub_080312D8`, `sub_0803DD88`, `sub_0803DDB0`, `sub_0803DDD8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 111/633 linked)
- Functions: `sub_080433F4`, `sub_080608D4`, `sub_08068558`, `sub_0806FDB4`, `sub_08072CC0`, `sub_0802E1EC`, `sub_08044D8C`, `sub_080475C4`, `sub_080475F4`, `sub_08071FAC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 121/633 linked)
- Functions: `sub_08033C1C`, `sub_0803484C`, `sub_08034FF8`, `sub_080361A8`, `sub_080428C4`, `sub_080604A4`, `sub_08060798`, `sub_080615EC`, `sub_0806EE24`, `sub_08033E3C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 131/633 linked)
- Functions: `sub_08034360`, `sub_08034FBC`, `sub_080447CC`, `sub_08062960`, `sub_08070C98`, `sub_08071FC8`, `sub_08073078`, `sub_0807339C`, `sub_0802D898`, `sub_08035908`
- make compare: OK

### 2026-09-17 — match_batch (+10, 141/633 linked)
- Functions: `sub_08042B28`, `sub_08042B50`, `sub_08044EE8`, `sub_08048D0C`, `sub_08050864`, `sub_080538A0`, `sub_08054108`, `sub_08056380`, `sub_08056AF0`, `sub_080626B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 151/633 linked)
- Functions: `sub_0806BE20`, `sub_0806FEFC`, `sub_08073184`, `sub_080731F4`, `sub_080739E8`, `sub_0802B930`, `sub_0803DCFC`, `sub_080405E8`, `sub_08045A84`, `sub_080720F0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 161/633 linked)
- Functions: `sub_0802BA4C`, `sub_0802E210`, `sub_080312B0`, `sub_080408C4`, `sub_08047594`, `sub_080628B4`, `sub_08062CC8`, `sub_080686B4`, `sub_0806FF28`, `sub_0802EECC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 171/633 linked)
- Functions: `sub_0802FD80`, `sub_08031124`, `sub_0803E440`, `sub_080400D4`, `sub_08040618`, `sub_08041394`, `sub_08041980`, `sub_08043944`, `sub_08043B58`, `sub_0804495C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 181/633 linked)
- Functions: `sub_08059C6C`, `sub_080611F0`, `sub_08062238`, `sub_08062D24`, `sub_080703FC`, `sub_08070AD4`, `sub_08070DF4`, `sub_08034788`, `sub_080347E4`, `sub_08035238`
- make compare: OK

### 2026-09-17 — match_batch (+10, 191/633 linked)
- Functions: `sub_080361CC`, `sub_08054558`, `sub_08061308`, `sub_08061BAC`, `sub_08062044`, `sub_08062CF4`, `sub_0806DEC8`, `sub_0806EBF8`, `sub_0806F430`, `sub_080733BC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 201/633 linked)
- Functions: `sub_0802B994`, `sub_0802E18C`, `sub_080320CC`, `sub_08033158`, `sub_08041858`, `sub_08060D28`, `sub_08062D50`, `sub_080674BC`, `sub_08069908`, `sub_08069948`
- make compare: OK

### 2026-09-17 — match_batch (+10, 211/633 linked)
- Functions: `sub_08069988`, `sub_080735B0`, `sub_080405A8`, `sub_0804BE80`, `sub_0804CA30`, `sub_0804D58C`, `sub_0805DA70`, `sub_08060220`, `sub_0806105C`, `sub_08062068`
- make compare: OK

### 2026-09-17 — match_batch (+10, 221/633 linked)
- Functions: `sub_08066BC4`, `sub_08067F98`, `sub_0806A580`, `sub_08070678`, `sub_08031368`, `sub_08042B78`, `sub_08042BB0`, `sub_08042C3C`, `sub_0806013C`, `sub_080603A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 231/633 linked)
- Functions: `sub_08061C48`, `sub_08062AC0`, `sub_0806D748`, `sub_080330F4`, `sub_08035020`, `sub_0805D1AC`, `sub_080699C8`, `sub_0806F174`, `sub_080726E0`, `sub_0802C62C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 241/633 linked)
- Functions: `sub_08030F00`, `sub_0803DBD0`, `sub_08059D08`, `sub_08060468`, `sub_080617C4`, `sub_080310F0`, `sub_0803A1E4`, `sub_08040088`, `sub_08066BF0`, `sub_08071F44`
- make compare: OK

### 2026-09-17 — match_batch (+10, 251/633 linked)
- Functions: `sub_080302A8`, `sub_08033F48`, `sub_08035204`, `sub_08060758`, `sub_08062758`, `sub_08068808`, `sub_0806B724`, `sub_0806F1A0`, `sub_08071E44`, `sub_0803C6B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 261/633 linked)
- Functions: `sub_08045AA8`, `sub_08046230`, `sub_0806209C`, `sub_08066AD4`, `sub_08069A18`, `sub_080712CC`, `sub_08071E04`, `sub_08038638`, `sub_08043BDC`, `sub_080603E0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 271/633 linked)
- Functions: `sub_080726A4`, `sub_0802B95C`, `sub_0803403C`, `sub_08034810`, `sub_08034894`, `sub_08033530`, `sub_0803E328`, `sub_0803E374`, `sub_0803E3C0`, `sub_08041348`
- make compare: OK

### 2026-09-17 — match_batch (+10, 281/633 linked)
- Functions: `sub_08043B90`, `sub_08045128`, `sub_08059DC8`, `sub_080618A8`, `sub_08061DC0`, `sub_08073218`, `sub_0803593C`, `sub_08043ADC`, `sub_08054454`, `sub_080611A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 291/633 linked)
- Functions: `sub_08062A74`, `sub_08063104`, `sub_0806D958`, `sub_08071B4C`, `sub_0802C5DC`, `sub_08033574`, `sub_08033EA4`, `sub_080385DC`, `sub_0803E258`, `sub_0803FDD0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 301/633 linked)
- Functions: `sub_08062C38`, `sub_08073A28`, `sub_0802E1B4`, `sub_08033A5C`, `sub_08041F88`, `sub_080424E8`, `sub_080435D8`, `sub_08061800`, `sub_080620D4`, `sub_08062B9C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 311/633 linked)
- Functions: `sub_08062BF0`, `sub_08033D90`, `sub_08040EF4`, `sub_080449C4`, `sub_08044A20`, `sub_0806F8C4`, `sub_08073440`, `sub_08073568`, `sub_0802C6AC`, `sub_08035884`
- make compare: OK

### 2026-09-17 — match_batch (+10, 321/633 linked)
- Functions: `sub_08035D1C`, `sub_08042BE8`, `sub_08044F64`, `sub_08046278`, `sub_08052934`, `sub_08062C80`, `sub_080680CC`, `sub_08057234`, `sub_0806C78C`, `sub_0803D4C4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 331/633 linked)
- Functions: `sub_08042F4C`, `sub_0804745C`, `sub_0805D99C`, `sub_08061D68`, `sub_08062640`, `sub_080677A8`, `sub_08043C28`, `sub_0806114C`, `sub_08067FC8`, `sub_08068020`
- make compare: OK

### 2026-09-17 — match_batch (+10, 341/633 linked)
- Functions: `sub_0806B3E8`, `sub_08038580`, `sub_08041DB4`, `sub_08061BE8`, `sub_08031300`, `sub_08033084`, `sub_08038D10`, `sub_0803E1F4`, `sub_0807179C`, `sub_0802D52C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 351/633 linked)
- Functions: `sub_0803413C`, `sub_08042784`, `sub_0806184C`, `sub_08071E84`, `sub_08071EE4`, `sub_0802C2B0`, `sub_08030938`, `sub_08033878`, `sub_080601C4`, `sub_080733E4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 361/633 linked)
- Functions: `sub_08042390`, `sub_08070604`, `sub_08073988`, `sub_08042718`, `sub_080473F8`, `sub_08067504`, `sub_0802D2C0`, `sub_08065560`, `sub_08069DBC`, `sub_08073114`
- make compare: OK

### 2026-09-17 — match_batch (+10, 371/633 linked)
- Functions: `sub_080338F0`, `sub_08042630`, `sub_08069894`, `sub_080426A4`, `sub_0805264C`, `sub_08052FC8`, `sub_080604C8`, `sub_08067F3C`, `sub_0802F520`, `sub_08042540`
- make compare: OK

### 2026-09-17 — match_batch (+10, 381/633 linked)
- Functions: `sub_080425B8`, `sub_08045C5C`, `sub_08059B74`, `sub_08061D00`, `sub_08031094`, `sub_08059AE0`, `sub_0802BC14`, `sub_08038D68`, `sub_080392D0`, `sub_08041E14`
- make compare: OK

### 2026-09-17 — match_batch (+10, 391/633 linked)
- Functions: `sub_08051BBC`, `sub_080610A8`, `sub_0806171C`, `sub_08071BA0`, `sub_08043638`, `sub_08065E0C`, `sub_08068798`, `sub_08070468`, `sub_0802E2F8`, `sub_08032D5C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 401/633 linked)
- Functions: `sub_0803E2AC`, `sub_0804737C`, `sub_080607BC`, `sub_08068118`, `sub_08036264`, `sub_080462D4`, `sub_08059C98`, `sub_08061AB8`, `sub_08038314`, `sub_0804B4B4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 411/633 linked)
- Functions: `sub_0804C324`, `sub_0804CED4`, `sub_08066224`, `sub_0806FDD0`, `sub_0807309C`, `sub_0803559C`, `sub_080360BC`, `sub_08061E8C`, `sub_08068E54`, `sub_08033DD4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 421/633 linked)
- Functions: `sub_08037318`, `sub_0806BC0C`, `sub_0806FE84`, `sub_08073910`, `sub_08034A68`, `sub_08035624`, `sub_0804A4E0`, `sub_0806A434`, `sub_0806B064`, `sub_0802C55C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 431/633 linked)
- Functions: `sub_0804AC3C`, `sub_0803E934`, `sub_0806A314`, `sub_0802BF04`, `sub_08062988`, `sub_0806A3A4`, `sub_08041C8C`, `sub_08048168`, `sub_08051504`, `sub_080523A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 441/633 linked)
- Functions: `sub_0806EE48`, `sub_08061564`, `sub_08062F90`, `sub_080691E4`, `sub_08031204`, `sub_08031C98`, `sub_08041774`, `sub_0804245C`, `sub_08068988`, `sub_080442FC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 451/633 linked)
- Functions: `sub_08062AF8`, `sub_0806306C`, `sub_0806C704`, `sub_080735DC`, `sub_080428F0`, `sub_08034618`, `sub_0803531C`, `sub_08056F84`, `sub_0806E7BC`, `sub_08044FB0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 461/633 linked)
- Functions: `sub_08041B74`, `sub_08059BD8`, `sub_0806E31C`, `sub_080419B0`, `sub_0806833C`, `sub_08070354`, `sub_08073AEC`, `sub_080302E0`, `sub_0803114C`, `sub_08068180`
- make compare: OK

### 2026-09-17 — match_batch (+10, 471/633 linked)
- Functions: `sub_08034568`, `sub_08049F98`, `sub_0804E17C`, `sub_08051578`, `sub_08053218`, `sub_080686F4`, `sub_0806A4D8`, `sub_08047624`, `sub_08067584`, `sub_08069B78`
- make compare: OK

### 2026-09-17 — match_batch (+10, 481/633 linked)
- Functions: `sub_0807000C`, `sub_0802C4A4`, `sub_08057274`, `sub_0806FF58`, `sub_0806E420`, `sub_0806FBF8`, `sub_080700CC`, `sub_0803E848`, `sub_080415FC`, `sub_080427E8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 491/633 linked)
- Functions: `sub_0804A028`, `sub_0802C314`, `sub_08070D44`, `sub_0802C3DC`, `sub_08035D68`, `sub_08062358`, `sub_08033978`, `sub_08047A94`, `sub_0804A438`, `sub_0804B40C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 501/633 linked)
- Functions: `sub_0804C27C`, `sub_0804CE2C`, `sub_0804E4F4`, `sub_080507B8`, `sub_08066B10`, `sub_0804E20C`, `sub_08035258`, `sub_080416C4`, `sub_08054494`, `sub_08035C64`
- make compare: OK

### 2026-09-17 — match_batch (+10, 511/633 linked)
- Functions: `sub_0806225C`, `sub_080688C8`, `sub_08032604`, `sub_08051444`, `sub_08037430`, `sub_0804EBF0`, `sub_0803C5DC`, `sub_0807027C`, `sub_0802E048`, `sub_0805E044`
- make compare: OK

### 2026-09-17 — match_batch (+10, 521/633 linked)
- Functions: `sub_0803C500`, `sub_080632F8`, `sub_08054CF4`, `sub_080553B8`, `sub_08063D68`, `sub_080353A0`, `sub_08038438`, `sub_080474AC`, `sub_0802D8DC`, `sub_0803FFB0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 531/633 linked)
- Functions: `sub_08052F0C`, `sub_0806DF38`, `sub_08030638`, `sub_08060D58`, `sub_08061628`, `sub_0804188C`, `sub_08069270`, `sub_0806121C`, `sub_08070188`, `sub_0803B078`
- make compare: OK

### 2026-09-17 — match_batch (+10, 541/633 linked)
- Functions: `sub_08062790`, `sub_08068EC0`, `sub_0803E0CC`, `sub_080333E4`, `sub_08072A38`, `sub_0806B2F0`, `sub_08060C30`, `sub_080429CC`, `sub_08036A68`, `sub_080593A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 551/633 linked)
- Functions: `sub_08068598`, `sub_08068418`, `sub_08062D80`, `sub_08062E88`, `sub_0806F05C`, `sub_08038F30`, `sub_0803D284`, `sub_08069A60`, `sub_0806B5C8`, `sub_0803D51C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 561/633 linked)
- Functions: `sub_08035468`, `sub_0806211C`, `sub_08030F38`, `sub_0804109C`, `sub_08067BB8`, `sub_08034420`, `sub_0803019C`, `sub_08056250`, `sub_08065CD0`, `sub_0802BAD4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 571/633 linked)
- Functions: `sub_08043C70`, `sub_0803370C`, `sub_08067648`, `sub_08040680`, `sub_08035984`, `sub_0804BD38`, `sub_0804ED90`, `sub_080411EC`, `sub_08045D3C`, `sub_0804AE94`
- make compare: OK

### 2026-09-17 — match_batch (+10, 581/633 linked)
- Functions: `sub_08043420`, `sub_0804438C`, `sub_0806A6F8`, `sub_08040F4C`, `sub_08061EF8`, `sub_0802D3F0`, `sub_080737C0`, `sub_08044648`, `sub_08066FB8`, `sub_0804C8BC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 591/633 linked)
- Functions: `sub_080444BC`, `sub_0806314C`, `sub_080447E8`, `sub_0803139C`, `sub_0804AAF0`, `sub_08068BD4`, `sub_0806EEC8`, `sub_08032908`, `sub_08035AE0`, `sub_0804D420`
- make compare: OK

### 2026-09-17 — match_batch (+10, 601/633 linked)
- Functions: `sub_0803715C`, `sub_08056D68`, `sub_080348E8`, `sub_0802DEA0`, `sub_080618EC`, `sub_08070AF8`, `sub_08070930`, `sub_08035054`, `sub_08030D4C`, `sub_08068A08`
- make compare: OK

### 2026-09-17 — match_batch (+10, 611/633 linked)
- Functions: `sub_0803DEC8`, `sub_0802DCDC`, `sub_08045EF0`, `sub_08037508`, `sub_0806E060`, `sub_08056BA4`, `sub_0802D6D4`, `sub_0806EC20`, `sub_08048DB8`, `sub_08060E48`
- make compare: OK

### 2026-09-17 — match_batch (+10, 621/633 linked)
- Functions: `sub_08053690`, `sub_08067CE8`, `sub_0806F910`, `sub_0802ECD8`, `sub_0806B764`, `sub_08033188`, `sub_080706B0`, `sub_08054120`, `sub_0806960C`, `sub_080436B0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 631/633 linked)
- Functions: `sub_08044A8C`, `sub_0806C388`, `sub_0802FA94`, `sub_08032DC4`, `sub_08046E7C`, `sub_0804DB28`, `sub_08045198`, `sub_08045590`, `sub_0806C7D4`, `sub_08043DB4`
- make compare: OK

### 2026-09-17 — match_batch (+2, 633/633 linked)
- Functions: `sub_0804FFCC`, `sub_08039BD4`
- make compare: OK
