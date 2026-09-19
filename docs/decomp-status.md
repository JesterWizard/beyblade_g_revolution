# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

<!-- decomp-progress:start -->
| Metric | Value |
|--------|-------|
| Linked in ROM | **633/633** (100% peeled) |
| **Decompiled C (functions)** | **253/633 (40.0%)** |
| **Decompiled C (bytes)** | **11,446/90,272 (12.7%)** |
| Not opcode (C + readable Thumb) | 633/633 (100.0% fn, 100.0% bytes) |
| Readable Thumb | 380/633 (60.0%) |
| Opcode `.byte` embeds | 0/633 (0.0%) |
| `src/matched/*.c` | 633/633 |
| Phase | **3b in progress — replace opcode stubs with semantic C / readable Thumb** |
| Battle semantic C | 40/160 (25.0% fn, 7.0% bytes) |
| Counter | [`decomp-progress.svg`](decomp-progress.svg) · [`decomp-progress.json`](decomp-progress.json) · [`decomp-functions.md`](decomp-functions.md) |
<!-- decomp-progress:end -->

## Batch log

### 2026-09-20 — deep permuter search on 6 near-miss candidates (0 landed, 246/633 unchanged)
- Investigated the 12 flagged near-miss candidates; deprioritized `sub_0802B994` and `sub_0802C2B0` after finding prior/fresh permuter base scores of 2055+ (not simple register-order quirks — real structural mismatches), and `sub_08046278`/`sub_0806F910` after m2c failed and manual C reconstruction couldn't reach the retail register-spill shape (extra live r8/r9 across a leaf with no calls) even with correct logic.
- Ran full-budget (~15-18 min wall clock, `-j2`–`-j4`, `--stop-on-zero`) decomp-permuter searches on the 4 genuinely clean near-misses (base score exactly 100 or a 78-79% same-size DIFF, correct logic, differing only in agbcc's register/instruction-order choice):
  - `sub_08062D50` (RGB15 pack → 0xA0<<19 VRAM slot): base 78.3% (36/46 bytes), plateaued at score 120 across ~47,000 iterations across two runs (default + weighted `perm_temp_for_expr`/`perm_reorder_stmts`/`perm_duplicate_assignment` passes). Manual reconstruction (12+ hand variants: mask as separate var, `register asm("r3")` pin, split-statement forms, 3-temp forms) reproduced the 78% shape repeatedly but never the retail `push {r4,r5,r6,lr}` 3-register spill from a 2-register-sufficient algorithm.
  - `sub_08062CF4` (same pack, fixed `0x05000200` OBJ palette base): base 79.2% (38/48 bytes) via `match_function.py` (real headers), plateaued at score 120 across ~48,000 iterations. Note: an isolated typedef-only test compile (matching the permuter's stripped base.c) misleadingly showed a byte-exact match — real `global.h` headers change codegen enough that only `match_function.py`'s output is trustworthy.
  - `sub_0802C55C` (Unk1694 slot match-and-flag, single `bl` to `sub_0803E0CC`): base 100, ran 129,548 iterations, never improved.
  - `sub_0802E2F8` (ROM table `0x08077AC0` linear scan + `_080740B0` tail-call proportional-damage calc): base 100, ran 80,702 iterations, never improved.
- Also explored adding a `struct Unk08D0Table` type to unlock `sub_08062B9C` (bitmask+word-array clear loop at `*gUnk_030008D0`, base 100) but the macro promotion broke the existing verified match on `sub_08062AC0`; reverted cleanly before touching headers permanently.
- **Conclusion, consistent with 4 prior sessions' notes in this log**: this batch of near-misses is the documented agbcc leaf-function register-allocation/extra-push quirk, and it is resistant to both hand C rephrasing and decomp-permuter's randomization passes at real (tens-of-thousands-of-iterations) search depth — not just short 3-5 min runs. No functions integrated, no partial/broken state left in `src/matched/` or `include/`.
- `make compare`: OK (unchanged, verified before and after)
- Decompiled C: 246/633 (38.9%) — unchanged

### 2026-09-19 — semantic C +3 (239→242/633); Unk0798 CpuFill helpers + affine register store
- Matched `sub_08060D28` and `sub_08061308` (both `_08073C4C` CpuFill-style calls building dest from `gUnk_03000798`'s `unk5D`/`unk94` fields, via `*0x080BB8BC`) — needed a `register u32 tmp asm("r0")` pin per field load to steer agbcc's register choice to match retail's `ldrb r0`/`ldrh r0` then shift-into-r1/r2 pattern; a plain local variable picked the wrong register.
- Matched `sub_08069A18` (write 4 halfwords to one of two affine I/O register blocks selected by an enum-like `u8` arg) — first `if`/`else if` shape 51/72 (retail uses `beq`/`beq`/`b` positive branches, not `bne`-invert-and-skip); switching to an explicit `switch` statement landed 72/72 exactly.
- Near-miss, reverted (no partial state left): `sub_08061BE8` (74/96, `Unk0770` slot pop + `_08073C4C` — pool-load ordering and a `*(void**)slot->unk00` extra deref close but not exact), `sub_08061DC0`/`sub_08061D68` (BGR pack helpers, same-size DIFF, register-choice only), `sub_08062A74` (88.2%, flag-bitmap set + `_08073C4C` + table store, one register off), `sub_08068020`/`sub_08066BF0` (table-walk helpers, same-size DIFF), `sub_08069894` (90.6%, three back-to-back IWRAM byte stores 0x108/0x1A8/0x1B0 — agbcc folds two via `adds`-from-cached-address when retail doesn't; no C rephrasing tried stopped the fold).
- `make compare`: OK
- Decompiled C: 239 → 242/633 (37.8% → 38.2%)

### 2026-09-19 — semantic C +2 (231→233/633); Unk705DC list walk + Unk047C init
- Matched `sub_080712CC` (walk `Unk712CC.unk14` linked `Unk705DC` list `unk1C-1` times, `sub_080705A4` each node, store flag at `unk0E`). First shape was 53/56 same-size (`ldr r0,[r7,#0x1C]; sub r4,r0,#1`). Split to `n = a->unk1C; n = n - 1;` → 56/56. Added `Unk705DC.unk04` next-pointer; re-verified `sub_080705A4` / `sub_080705DC` / `sub_08034788` still MATCH. Also split `Unk62044.unk10`/`unk14` (re-verified `sub_08062044` / `sub_0806209C`).
- Matched `sub_080405A8` (zero `Unk047C.unk80C`/`unk808`, fill `unk00[0..0x1FF]` with `-1`, reload `*gUnk_0300047CLoc` each store). Added `gUnk_0300047CLoc`. Pin `r3` as the IWRAM address, copy to `r4` after the head stores; `unk808` is `adds r0, r0, r1` with `r1=0x808` then store through `unk00[0]`.
- Near-miss (readable Thumb kept): `sub_08042B28`/`sub_08042B50` 36/40 same-size (`lsl` before `ldr` of the ROM table vs retail `ldr` then `lsl`); `sub_080620D4` 64/72 leaf uses `r7` without `push {r7}`; `sub_08071F44` mid-function IWRAM pool; `sub_0806D748` unused `u16` r3 DCE + epilogue `u8` truncate; `sub_0806F1A0` packed `i++` via `+0x10000` in-loop is close; `sub_08073568` true proto is 3-arg (`dest, n, size`).
- `make compare`: OK
- Decompiled C: 231 → 233/633 (36.5% → 36.8%)

### 2026-09-19 — semantic C +4 (227→231/633); per-function score ledger
- Matched `sub_08061C48` (pop one `Unk0770` slot at `gUnk_03000794`/`gUnk_03000770`, free via `sub_0806A434`) — needed `tmp[]` + `r4`/`r5` pool pin, same trick as `sub_08033C1C`.
- Matched `sub_0806209C` (walk `Unk62044.unk0C[0..0x7F]`, `sub_0806FE84` each non-NULL then clear; typed `unk0C` as `void **`; re-verified `sub_08062044` still MATCH).
- Matched `sub_08073A28` (insert a byte into a string, shifting the tail) — first shape was 60/66 same-size; matching retail's `do { s[i+1]=s[i]; } while (i >= n)` plus the `(u16)(n-1)` truncation landed 66/66.
- Matched `sub_080618A8` (`Unk618A8` init, 6 halfwords + flags, two stack `u16` args) on the first real attempt once store order followed the disasm.
- Easy-win miss: smallest no-`push` helpers (`sub_08033958`, `sub_0806DEF4`, `sub_0806AC68`, …) are the documented agbcc-extra-`push {lr}` leaf-branch class (+4B). Prefer already-framed functions next.
- New ledger: [`decomp-functions.md`](decomp-functions.md) lists all 633 with completion % and `N/M` bytes. Status **matched** vs **byte-identical DIFF** (same size, only pool/reloc words differ — not counted as decompiled). `match_function.py --record` updates scores.
- `make compare`: OK
- Decompiled C: 227 → 231/633 (35.9% → 36.5%)

### 2026-09-19 — semantic C sub_08073218 (+1, 226→227/633); permuter batch running
- Matched `sub_08073218` (bounded string copy `src`→`dst` up to `n` bytes, zero-pads `dst[n-1]` on overflow, returns copied length) — took 4 iterations: first attempt had `src`/`dst` params swapped (re-read the disasm's `strb`/`ldrb` operand order to fix), second needed the branch *and* condition-polarity both flipped to match retail's physical block order, third needed `n`/`i` retyped `u32` (not `s32`) since retail's bounds check is `bcs`/unsigned, not `bge`/signed.
- Tried `sub_08031300` (`Unk312EC` counter/callback dispatch) and `sub_08069988` (4-way hardware-register-address switch) — both reverted; the switch-style one hit the already-documented agbcc-leaf-push wall again, `sub_08031300` got to a 2-byte gap (missing explicit `u8` truncation on a ternary) before running out of shape variations that helped.
- `sub_08071E04` (struct-init + ROM-table clamp-and-index) also near-missed and was hform-imported into the permuter batch (see below) — left its header prototype exactly as it was (2 params) since the correct 3-param signature isn't verified yet and touches a naked-asm caller.
- 9 near-miss functions now running through decomp-permuter in the background (added `sub_08071E04` to the 8 from the prior entry).
- `make compare`: OK
- Decompiled C: 226 → 227/633 (35.7% → 35.9%)

### 2026-09-19 — semantic C sub_08038D10 + sub_0803E1F4 (+2, 224→226/633); 8 near-misses handed to the permuter
- Matched `sub_08038D10` (dispatches `BattleWork.unk023C[4]` slots to `sub_08070AD4`/`sub_08070678` based on a shared ROM/RAM table `gUnk_030003E0[a->unk2FC+i]`) — new `struct Unk7069C unk023C[4]` field carved into `BattleWork` right where the earlier `Unk38314.unk2FC` boundary sits (0x23C–0x2FC), moved `struct Unk7069C`'s definition earlier in the header so it can be nested by value. Took a few iterations to realize the "array" field on the caller's struct is actually an `s32` *index* added to a separate global table, not an array of pointers on the struct itself.
- Matched `sub_0803E1F4` (search `MainWork.unk08D0[]` by two new fields — `unk23`/`unk1C` — plus the existing `unk087C` flag) — same-size DIFF on the first real attempt; the only bug was the two `s16` parameters being compared against the wrong struct fields (swapped `a`/`b`). New `unk23` field added to the existing `struct Unk8D0`; re-verified `sub_0803E258` (which also uses this struct) still matches.
- **Near-miss batch handed to decomp-permuter**, running in the background (`-j1` each, `--stop-on-zero`, imported via `tools/decomp/permuter/import_function.py`): `sub_08062068`, `sub_08042C3C`, `sub_08067F98`, `sub_08034810`, `sub_08040088`, `sub_08042BB0`, `sub_080312B0`, `sub_0803DCFC`. All 8 are same-or-near byte count as retail with correct logic (verified via `match_function.py` DIFF), blocked only on a specific register-allocation choice or branch-fold agbcc makes that no C rephrasing tried could steer — exactly the class the permuter's random search is built for. `src/matched/*.c` reverted to naked-asm for all 8 while permuting (the permuter works from its own `nonmatchings/<fn>/base.c` copy); whichever ones land should be integrated from the permuter's zero-score output, not re-derived by hand.
- `make compare`: OK
- Decompiled C: 224 → 226/633 (35.4% → 35.7%)

### 2026-09-19 — semantic C sub_08031368 (+1, 223→224/633); pace note for the 40% ask
- Matched `sub_08031368` (reverse array-of-pointers search skipping index 0, returns two fields via out-params) — matched on the first real attempt once the loop bounds were traced precisely (`for i = n-1 downto 1`, index 0 never checked — a real, deliberate asymmetry, not a bug).
- Extensive near-miss work, all reverted (no partial/broken state left): `sub_08062068` (48B=48B; a `switch`/if-chain 3-way branch where retail's second comparison is a genuine `bcc` unsigned-less-than against 1 that no phrasing — `c<1`, `(u32)c<1`, `(s32)c<1`, `switch` case order — stopped agbcc from folding to `beq ,#0`; likely needs the exact original variable rather than a derived comparison), `sub_08067F98` (56B vs 48B; a variable-stride "linked record" walk needs real byte-pointer arithmetic for the next-offset, which added register pressure beyond retail's shape), `sub_08042BB0` (48B vs 56B; a ROM-table search where retail tracks the loop pointer in *two* registers rather than one — same "independent per-access addressing beats a cached pointer" lesson as `sub_08046230`, got the register set to match but 8 bytes still differ).
- **Honest pace check against the 40% target (253/633):** today's realized rate across ~15 attempted functions is roughly 1 landed match per 3-5 real attempts, several needing multiple disassembly-diff rounds each. A large fraction of what remains in the small/easy tier is gated by one of: the confirmed-unfixable agbcc-extra-push-on-leaf quirk, still-fully-naked large callees (`sub_0804109C`, `sub_08060E48`, the `sub_08061E8C` particle-effect group), or raw unnamed ROM/RAM addresses shared with not-yet-understood structs. Getting from 224 to 253 at this rate is a lot of ground; flagging this now rather than after stalling silently.
- `make compare`: OK
- Decompiled C: 223 → 224/633 (35.2% → 35.4%)

### 2026-09-19 — semantic C sub_08034788 (+1, 222→223/633)
- Matched `sub_08034788` (midpoint of two `Unk705DC*`'s `unk0C`/`unk10` fields) — needed an explicit `(s32)` cast on the sum before the `>>1`, since retail used `asrs` (arithmetic/signed shift) on what the shared struct currently types as `u32`. Cast locally rather than changing `Unk705DC.unk0C`/`unk10` to `s32` globally, since 5 other matched functions already depend on the current (unsigned) field type and re-typing them wasn't verified safe this session.
- Near misses reverted: `sub_080312B0` (40B=40B, only a `ldrh` register choice — r0 vs r5 — differs; tried caching the shifted value in an explicit local before/after the other stores, no effect), `sub_0803DCFC` (48B=48B modulo the still-placeholder `gUnk_0807A1F4` pool word *and* one register-choice byte pair on the initial parameter copy; branch-order fix got it very close but the r1-vs-r2 allocation didn't move with any source reshaping tried).
- Re-confirmed the "agbcc extra push on leaf" quirk (see entry below) hits yet more candidates when tried fresh: `sub_08062684` (24B vs 20B, null-check-and-3-field-write shape, same class as `sub_0802B994`/`sub_0802C62C`) — not pursued further, matches the already-documented pattern exactly.
- `sub_0806105C` (battle-adjacent, calls `sub_08060E48`) skipped: its only callee is a ~200-line glyph/font-rendering function still fully naked-asm — too large and unrelated to hand-convert as a side dependency.
- `make compare`: OK
- Decompiled C: 222 → 223/633 (34.9% → 35.2%)

### 2026-09-19 — correction to the ROM-symbol note below, +1 more match (221→222/633)
- **Correction:** the "ROM-symbol tooling gap fix" logged in the entry below was based on a misdiagnosis. `integrate_c.py` doesn't actually link `src/matched/*.c` into the final ROM at all — once a function verifies byte-perfect, `write_matching_bytes()` freezes the *verified retail bytes* directly as `.short` literals in `asm/matchings/<fn>.s`, and that frozen file (not the C source) is what gets linked. So `sub_080435D8` matched and integrated correctly regardless of whether `gUnk_08094BB4` ever resolves as a real symbol — the `rom_tail.s` incbin split was unnecessary, and it silently got wiped by the next `gen_rom_layout.py` regeneration anyway (confirmed: reverted the split, `make compare` still OK). Not reapplying it. The underlying limitation is real for *re-verifying* a match with `match_function.py` standalone (it'll always show that pool word as a placeholder) but has no effect on `make compare` / actual integration once `write_matching_bytes` has run once. No tooling change needed after all.
- Matched `sub_08044D8C` (sums `a[1..0x7D7]` as `u32`) — needed retail's exact loop shape: `u32 *p = a + 1;` declared *after* the sum/bound locals (not `a++` inside the loop), post-increment `*p++` (not pre-increment), and critically **unsigned** loop counter/bound (`u32 i`, `u32 bound`) — a signed `s32 i < bound` compiles to `blt`, but retail used `bcc` (unsigned), 1 byte different despite otherwise-identical codegen. Took 4 iterations narrowing from "right idea, wrong pointer-arithmetic shape" to exact match.
- `make compare`: OK
- Decompiled C: 221 → 222/633 (34.9% → 35.1%)

### 2026-09-19 — root-caused the agbcc-extra-push-on-leaf quirk (no fix found, no change to counters)
- Directly tested the recurring "agbcc extra push {lr} on leaf" blocker (already hit 10+ times across sessions: `sub_0802D8C4`, `sub_08061BDC`, `sub_0802B994`, `sub_0802C62C`, `sub_08043B58`, `sub_08062684`, etc.) rather than rediscovering it per-function. Compiled a minimal true-leaf function (`if (a) { 3 field writes }`, no calls, `bx lr` in retail) directly with `tools/agbcc/bin/agbcc` under every combination of `-fomit-frame-pointer`, `-fprologue-bugfix`, and with/without `-mthumb-interwork` — **agbcc emits `push {lr}` / `pop {pc}`-equivalent framing in every case**, with no flag that suppresses it for a leaf with a conditional branch.
- **Conclusion:** this is not a source-shape or flag problem — agbcc (this vendored 2.9-arm-000512 build) appears to always frame any leaf with more than a trivial straight-line body, while retail's binary does not, meaning retail's leaves either used a different/patched compiler build, or (more likely for the null-check-and-store shape specifically) were hand-written in assembly rather than compiled from C. **Stop trying C-shape variations on this class** — every remaining true-leaf candidate (no `bl`, ends in bare `bx lr`, retail push-list shorter than 4 registers) will hit this. Either leave them as naked-asm (current default) or feed them to the permuter in bulk; don't spend more manual-C-iteration time on them individually.
- `make compare`: OK (no functional changes)
- Decompiled C: 221/633 unchanged

### 2026-09-19 — fixed the ROM-symbol tooling gap, landed sub_080435D8 (+1, 220→221/633)
- **Root-caused and fixed** the "can't reference a raw ROM rodata address from new C" gap flagged last batch: `asm/rom_tail.s`'s single giant `.incbin` (0x08074146..ROM end) has no symbols inside it, so `extern const T x[]` at a ROM address a function needs can never link. RAM globals (`gMainWorkPtr` etc.) dodge this entirely — the C headers `#define` them as raw address literals, never as real `extern` symbols, so they don't depend on `ram_map.s`'s `SET_DATA` for *linking* (that file's symbols are for other assembly, not C).
- Fix: split `rom_tail.s`'s incbin in two at the needed offset and inserted a `.global gUnk_08094BB4` label at the split point — same total bytes, zero-cost, `make compare` byte-identical before/after the split alone.
- With the real symbol in place, `sub_080435D8` (blocked last batch on the pool-word-only diff) links and matches for real: confirmed by a full `make compare` (not just the standalone `match_function.py` check, which still can't link against `rom_tail.o` and will keep showing that word as `00000000` — that's a known, harmless limitation of the standalone checker, not a sign of a real mismatch, *once the ROM symbol actually exists*). Manifest updated by hand (`kind: asm` → `semantic`) since `integrate_c.py`'s internal verify still uses the standalone checker.
- **Reusable pattern for next session:** any future "known ROM address, no symbol" blocker (there may be others in the `sub_080436B0` family / similar table lookups) can be fixed the same way — find which `rom_gap_*.s`/`rom_tail.s` incbin covers the address, split it, add a `.global` label, confirm `make compare` stays green on the split alone, then the function's `extern` reference will link for real even though `match_function.py` standalone still shows a stale pool word.
- `make compare`: OK
- Decompiled C: 220 → 221/633 (34.8% → 34.9%)

### 2026-09-19 — semantic C (+1, 219→220/633), continued near-misses
- Matched `sub_08044A20` (`MainWork.unk17B4`/`unk17B8`/`unk17C4`/`unk17C8` swap-then-invalidate, mirrored to `unk044C`/`unk0450`) — matched first try; new fields carved from `filler_0428`/`filler_17A0`, offsets cross-checked with `arm-none-eabi-gcc offsetof`.
- Re-attempted `sub_08043B90` with the now-real `sub_08073440` callee — still the same confirmed 1-instruction near-miss from last session (76B, tail re-reads `entry->unk00` instead of reusing the loop-exit register); tried `for`, `while`, `do-while(1)+break`, and a cached-key `for(;;)` form, all landed on the identical extra-`ldr` shape. Genuinely needs a permuter, not more C reshaping — parking it.
- New near-misses found and reverted: `sub_08043B58` (52B vs 54B — same agbcc-extra-push-on-leaf class as `sub_0802B994`/etc., confirmed again on a linked-list-of-pointers search), `sub_08042390` (96B vs 98B — nested-if reconstruction is 2 bytes *shorter* than retail because agbcc shares a `x-refX` subexpression across two basic blocks that retail's source apparently recomputed independently; tried duplicating the expression via redundant if/else nesting, no effect — CSE happens regardless of source phrasing here), `sub_08042784` (108B vs 100B — ring-buffer struct `Unk0538` extension is very likely right structurally but the compiled shape diverges enough — 8 bytes — that it needs more investigation, not a quick fix).
- `struct Unk0538` (`*gUnk_03000538`) extended from the existing 2-byte cursor (`sub_080428C4`) to a full 0x144-byte ring buffer (`unk04[32]`/`unk44[32]`/`unkC4[32]`) — verified `sub_080428C4` still matches unchanged.
- New `struct Unk0554` (`*gUnk_03000554`) and `gUnk_03000538`/`gUnk_03000554` pointer macros added to `ram_map.h`; `sub_08043974` updated to cast the pointer directly (`(u32)gUnk_03000554`) instead of double-dereferencing, to stay consistent with the new typed macro — still matches.
- `sub_080435D8` reconstructed correctly (96B=96B, only the not-yet-linked `gUnk_08094BB4` ROM-table pool word differs) but **could not be integrated**: referencing a raw ROM rodata address with no linker symbol isn't supported by the current `match_function.py`/`integrate_c.py` flow (no `SET_DATA`-style ROM equivalent exists yet, only IWRAM/EWRAM). Flagged as a tooling gap, not a logic problem — worth adding ROM-address symbol support to `asm/ram_map.s` conventions.
- `make compare`: OK
- Decompiled C: 219 → 220/633 (34.6% → 34.8%)

### 2026-09-19 — semantic C (+5, 214→219/633)
- Matched `sub_08046230` (2-slot `MainWork.unk16B0[]` reset — retail addresses each of the 3 fields as its own independent computation rather than one struct-member access; using explicit `gMainWorkPtr->unk16B0[a].unkNN` per field, not a cached pointer, produced the byte-identical shape).
- Matched `sub_080330F4` (`BattleWork.unk1F90`/`unk1F94`/`unk1F98` trio; the `if(a>=0)` branch had to be written as the *positive* case first — agbcc mapped my initial `if(a<0){...}else{...}` to the opposite fallthrough retail used — and the else-branch literal was `0x800`, not `0x800000` as first guessed from the raw `movs #0x80; lsls #4` bytes).
- Matched `sub_08073440` (byte-array 3-way compare, `-2`/`-1`/`0`/`1`, strcmp-shaped) — matched first try once the existing `s32 sub_08073440(void*, void*)` prototype was reused verbatim.
- Matched `sub_0803E258` (0x53-slot `MainWork.unk08D0[]` search by `unk1C` key + `unk087C[]` flag byte, returns `&unk08D0[i]`) — new `struct Unk8D0` (0x28-stride) and `unk087C[0x53]`/`unk08D0[0x53]` fields added, offsets cross-checked with `arm-none-eabi-gcc offsetof`.
- Matched `sub_08038638` (`Unk3CC.unk22[]` countdown + `sub_080385DC` retrigger) — new `struct Unk3CC` (`*gUnk_030003CC`, `unk00[16]`/`unk20`/`unk22[16]`) plus the `gUnk_030003CC` pointer macro in `ram_map.h`. Needed retail's exact dual-read shape: an unsigned `u16 raw` copy of the field used only for the decrement math, kept separate from the `s16`-typed field read used for the `>0`/`==0` comparisons — collapsing them into one read landed 4-8 bytes short every time.
- Near misses parked (reverted to naked-asm, not committed): `sub_08043B90` (76B, 1 redundant instruction — final return re-reads `entry->unk00` instead of reusing the register from the loop-exit test), `sub_08052934` (84B, 2 instructions swapped — `ldr`+`ldrb` order differs after adding a `Unk995AC`/pointer-indirection struct for the `0x080995AC` table), `sub_08033574` (80B, 1-byte pool-constant offset differs — `unk1FE6`-relative addend came out `0x3B` instead of `0x3A`, points 1 byte before `unk1FAC`; likely fixable with a different statement order but not found this session).
- `make compare`: OK
- Decompiled C: 214 → 219/633 (33.8% → 34.6%)

### 2026-09-19 — struct scaffolding + 2 new blocks (214/633 unchanged)
- Split `struct BattleWork` filler to name `unk19C[4]` (`struct Unk62044`, 0x19C/0x1C4/0x1EC/0x214 — confirmed via agbcc offsetof cross-check); moved `struct Unk62044` earlier in `unknown-types.h` so it can be nested by value. Added new `struct Unk38314` (countdown @0x2FC, flag @0x304).
- Attempted hand-conversion of `sub_08038314` and `sub_08045C5C` (both top-of-queue battle candidates). Both reconstruct the correct logic (verified via `match_function.py` DIFF — same/near-same size, only instruction-order/register-alloc differences) but agbcc lands on a different register choice than retail in each case. 20k+ permuter iterations on `sub_08038314` never found a zero (floor stuck at score 70). Documented both in `decomp-queue.toml` as blocked (needs permuter); see reasons there.
- `sub_08062D50` heads-up from previous session confirmed correct: it's the same BGR555-pack register-swap shape as blocked `sub_08062CF4` and is already parked as a naked-asm placeholder, not a fresh candidate — no action needed.
- `make compare`: OK (no functional changes, only header/type scaffolding)
- Blocked (documented): 29 → 31

### 2026-09-19 — moved down queue, 4 more agbcc-leaf blocks (214/633 unchanged)
- Worked down the "battle=2" tier (`sub_08033188`, `sub_0807309C`, `sub_08037430`, `sub_0803C5DC`, `sub_0803C500`, `sub_08036A68`, `sub_0803D51C`, `sub_08038F30`): all depend on a shared cluster of still-naked, multi-arg callees (`sub_08061E8C`, `sub_08073AEC`, `sub_08061EF8`, `sub_080735DC`, `sub_0802C314`, `sub_0806A3A4`/`sub_0806A4D8`) with no established prototypes — hand-converting the callers would mean guessing signatures. Skipped rather than risk wrong prototypes; someone should prototype `sub_0807309C`'s allocator group first to unblock this whole tier at once.
- Dropped to "battle=1" tier and found a **systemic pattern**: `sub_0802B994`, `sub_0804495C`, `sub_0802C62C`, `sub_0803DBD0` all reconstruct provably-correct logic (verified via `match_function.py`, `sub_0802C62C` even hit byte-identical *size*, 64=64) but agbcc inserts a `push{lr}...pop{r1};bx r1` leaf frame that retail's build doesn't have (`bx lr` direct, or a tighter push set), no matter which C shape/declaration-order is tried. This is the same class as the already-documented `sub_0802D8C4`/`sub_08061BDC`/`sub_08062634`/`sub_08061E40` "agbcc extra push {lr} on leaf" blockers — now confirmed to hit small ROM-table-lookup and counting-loop leaves too, not just null-check leaves. 7000+ permuter iterations on `sub_0802C62C` (the closest, byte-count-identical case) never found a zero, floor stuck at score 95. All 4 documented in `decomp-queue.toml`.
- **Takeaway for next session:** this agbcc leaf-framing quirk is now confirmed across ≥9 functions in 3+ shapes (null-check leaf, counting loop, table lookup, table copy). Worth investigating directly — e.g. does forcing `-Wl,--no-...`/a different agbcc leaf heuristic, or an explicit `register` hint, suppress the frame — before spending more permuter cycles rediscovering it function-by-function.
- `make compare`: OK (no functional changes; all attempted `.c` files reverted to naked-asm since none reached a byte-perfect match)
- Blocked (documented): 31 → 35



### 2026-09-18 — Semantic audit fix (+15 prototypes) + near-miss batch

- **Prototype fixes:** added `sub_08061BE8`; fixed `sub_08033F24` (`sub_08072CC0(a)`), `sub_080400D4` (cast), `sub_08070678` (`BtlObj` cast)
- **Semantic audit:** **0/182 broken** (was 15 compile failures + 4 same-size DIFF reverted earlier)
- `near_miss_batch.py`: `--no-m2c` for faster runs; blocked `sub_080473E4` (dual IWRAM CSE, permuter best score ~5)
- Near-miss still open: `sub_0803DD60` family (pool order), `sub_0806FEFC` (leaf `push {lr}`), `sub_0802C62C` (loop regs)
- `make compare`: **OK**

### 2026-09-18 — Near-miss triage + semantic audit

- Added `tools/decomp/near_miss_batch.py` / `.sh` — seeds + c_patterns on readable Thumb; `--list-broken` audits semantic C
- Added IWRAM pointer-slot macros in `ram_map.h` (`gBattleWorkPtrLoc`, `gMainWorkPtrLoc`, …) for pool-pin matching
- **Semantic audit:** 4 integrated files failed `match_function.py` (same-size DIFF) — reverted to verified asm:
  - `sub_08033530` → readable Thumb (`subs r2, #0x6C` offset reuse; blocked in queue)
  - `sub_08033F48` / `sub_0803403C` / `sub_0803413C` → opcode embed (semantic store order/reg alloc)
- Removed broken `sub_08033530` from `BATTLE_SEEDS`
- Near-miss attempts (same-size DIFF, permuter): `sub_0803DD60` family (pool order), `sub_080473E4` (dual IWRAM CSE), `sub_0806FEFC` (extra `push {lr}`), `sub_0802C62C` (loop reg alloc)
- 15 semantic files still fail agbcc (missing/wrong prototypes) — run `python3 tools/decomp/near_miss_batch.py --list-broken`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_0806F430` (`Unk4084` flags @ `gUnk_03004084` — bit 0x08/0x10 check, `sub_08067B98`; register `r0`/`r1` flow)
- Semantic C: `sub_08033C1C` (`Unk0380` @ `gUnk_03000380` — clear `unk09`/`unk0A`, call `sub_080358CC`; `r1` + `tmp[]` pool pin)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08031294` (`Unk312EC` init — OR flags on `unk00`/`unk01`, `unk04 = -1`, clear `unk0C`/`unk08`; register-pinned `r1`/`r2`)
- Prep (next): `BattleWork` `unk1FE6`/`unk2089`, `sub_08038638` proto, permuter seeds for `33574`/`473E4`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b battle semantic C (+1)

- Added `tools/decomp/battle_semantic_batch.py` / `.sh` — hand seeds + m2c/heuristics for battle readable Thumb
- Semantic C: `sub_08033530` (`gBattleWork->unk2088` branch → `33574` or `686D8`/`68418` on `unk1FAC`)
- Proto: `sub_08033530(void)` in `unknown-functions.h`
- Near-miss: `sub_080601C4` (r8 pool pin, 92B→84B), table-lookup family still pool-blocked
- `make compare`: **OK**

### 2026-09-18 — Phase 3b readable Thumb sweep (100% not opcode)

- Fixed `readable_asm.py`: prototypes from `unknown-functions.h` (pointer return types), multi-line `asm()`
- `readable_asm_batch.py --all`: converted remaining **227** opcode `.byte` stubs → readable unified Thumb
- Final fix: `sub_08069988` / `sub_08071E84` / `sub_08071F44` (header `void *` / `struct *` names)
- **0 opcode embeds remain** — not opcode **100%** (451 readable + 182 semantic)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b readable Thumb leaf batch (+20)

- Fixed `readable_asm.py`: preserve matched-file prototypes + multi-line `asm()` (`.byte` embeds now convert reliably)
- Converted 20 straight-line leaf opcode stubs → readable unified Thumb (`--kind asm`)
- Batch 1: `sub_0802D8C4`/`31294`/`33958`/`33F30`/`347E4`/`35908`/`361CC`/`42E78`/`473E4`/`61BDC`
- Batch 2: `sub_08061E40`/`62634`/`62684`/`62728`/`62CC8`/`62D24`/`68884`/`69F00`/`6A954`/`6AC68`
- Semantic C: `sub_080674BC` (dispatch table pointer via `0x030009B0`, register-pinned `r0`/`r2`)
- Other leaf semantic seeds still blocked (agbcc `push {lr}` / pool fold); `sub_080615EC` asm compile fail (branchy)
- `make compare`: **OK** — 264 opcode embeds remain (was 304); 187 readable Thumb (+40)

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_0802B8BC` (halfword table lookup via `gUnk_03000264`, `register asm` for `r0`/`r1` dest reg)
- Permuter on `sub_0803DD60`: best score **100** (~32k iters) — stays readable Thumb
- Leaf null-check stubs (`61BDC`/`62634`/`61E40`) still blocked by agbcc extra `push {lr}` on any branch
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_08072F94` (battle lookup byte via `gBtlLookupBase`/`Ptr` stack pool), `sub_0806DEC8` (indexed byte-chain walk), `sub_08066434`/`66440`/`6644C` (IWRAM `0x970` bytes @+0x34/+0x35), `sub_08062A1C` (store word @ `0x7B0+0x114`), `sub_0806639C` (ROM table `0x80BA1A8` indexed by `gUnk_03000964`)
- Types: `UnkDEC8`/`UnkDEC8Head`; protos fixed (`66434`/`66440` as `u8`, `615EC` as `u16`, `62A1C` as `u32`, `6639C` as `void *`)
- Permuter seeds added in `import_function.py` for pool-order leaves
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+4)

- Semantic C: `sub_0802D898` (write `0xFFFFF800` into `Unk026C->unk08` coords), `sub_0806EE24` (copy `unk358` to DISPCNT, set `unk356`/`unk355`), `sub_0802D3F0` (free `unk08`–`unk40` via `6FE84`, then `6A434` on `*0x03000270`), `sub_0802D8DC` (sync `Unk705DC` overlays via `2E18C`/`2E1B4`/`2E210`)
- Grew `Unk026C` (`unk08`–`unk40` as `Unk705DC *`, `unk48`/`unk4C`), `Unk705DC` (`unk08`/`unk0C`/`unk18`), `MainWork` (`unk0424`, `unk0878`, `unk1838`/`unk183A`), `Unk0798` (`unkA2`); added `Unk6EE24`/`Unk617C4`
- Near-miss: `sub_0802D52C`/`2E048`/`312B0`/`61800` (same-size dest regs), `sub_0802D6D4` (pool order C000 vs 63CC), `sub_0802DEA0` (CSE of `0xFFFFC000`), extra-`lr` leaves (`2D8C4`/`615EC`/`61BDC`/`617C4`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+5)

- Semantic C: `sub_080603A4` (optional `71FC8` on `unk177C` then store `unk1819`), `sub_080705A4` (pack 2 bits into `unk10` at bit 10), `sub_080705DC` (pack 4 bits into `unk14` at bit 12), `sub_0802D598` (clear `Unk026C` then write `0xFFFFC000` into inner +8/+0xC), `sub_08061610` (low 4 bits of arg into `unk96` at bit 12)
- Grew `Unk705DC` (`unk10`), `Unk0798` (`unk96`), `Unk026C`/`Unk026CInner`, `MainWork` (`unk15C8`–`unk15D2`), `Unk447CC` (`unk00`), `Unk6FDB4` (`unk22`); added `Unk2C314`; `sub_0803DD88` now takes `s32`
- Rematch: `sub_080312EC` (`(u8)unk01` into `705DC`)
- Near-miss: `sub_0802C62C`/`2B8BC` (same-size dest regs), `sub_0802C5DC`/`2C2B0` (slot+off reload vs rematerialize), `sub_080447CC` (unk18 in r1 vs r0), `sub_08042B78`/`42BB0` (pool in middle), extra-`lr` string leaves (`73078`/`731F4`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_080611A4` (alloc `0xAC` into 790/798/794 slots + CpuFill via `*0x080BB8BC`), `sub_08059C98` (first empty stride-`0x3C` slot + optional `6A3A4`), `sub_0806F8C4` (list integrity checks via `67B98`), `sub_080680CC` (key walk then `68180`), `sub_080408C4` (`2C314` then `3DD88`), `sub_0802B95C` (stride-12 search via `2B994`/`73440`)
- Grew `Unk0798` (`unk5C`/`unk88`), `Unk59C6C` (full 0x3C), `Unk0770` (`unk04`/`unk06`), `Unk346C0Inner` (`unk00`); added `Unk59C98Src`/`Unk59C98Owner`/`Unk680CC`/`Unk2B95C`; `sub_0803DD88` now returns `s32`
- Near-miss: `sub_08062BF0`/`62C38` (ble/bge skip 0 vs 1), `sub_08059B74` (bne skip 3 vs 6), `sub_08062A74` (p in r2 vs r1), `sub_08061308`/`60D28` (ldrb r1 vs r0), `sub_080615EC` (extra `lr` on leaf)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_08030F00` (copy inner `unk08`/`unk0C-0x1000`, optional `70354` from `unk30`), `sub_08033EA4` (`726A4` to BG pal + `72A38`), `sub_0803C6B8` (`74B40` pair into `74798`/`74634`/`74148`)
- Added `Unk30F00`/`Unk302A8`/`Unk6D748`/`Unk3E328`/`Unk71E84`; grew `Unk42E78`/`Unk59C6C`/`Unk705DC`/`Unk0798`; `_08073C44` now returns `u32`
- Near-miss: `sub_08062BF0`/`62C38` (ble/bge skip offset 0 vs 1), `sub_080473F8`/`71B4C` (pool-fold 630/638 and 40DC/410C), `sub_08059B74` (bne skip 3 vs 6), `sub_080611A4` (794 folded as 798-8)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08062640` (tick `unk20`/`unk1C`, optional `_08073C44` + `62684`), `sub_08066BC4` (indexed `705DC` then store 8 at +0x310)
- Added `Unk66BC4`
- Near-miss: `sub_0806F430` (dead `flags & 0x10` vs `cmp r1, #0`), `sub_08073A28` (string shift extra regs), `sub_08038638` (03CC reload vs rematerialize)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+4)

- Semantic C: `sub_08062AC0` (CpuFill `*08D0` + OBJ pal via `*0x080BB8BC`), `sub_0805DA70` (CpuSet `unk164` to `0x05000340`), `sub_08059D08` (optional `_08073C44` then free `unk0C`), `sub_0806D958` (optional `_08073C4C` then clear `unk80`/`unk84`/`unk88`)
- Added `Unk59D08`/`Unk6D958`; `_08073C44` prototype
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_08063104` (CpuSet `*08DC` to BG pal + free `*08E0`), `sub_08033A5C` (swap `34A68` slots then `35020`/`330F4`), `sub_08060468`/`60758` (alloc via `6A3A4` then CpuFill via `*0x080BB8BC`), `sub_0806A580` (first empty 16-byte slot), `sub_08062758` (walk `unk04` table into `62790`), `sub_08041394` (free 8 pointers at +0x220)
- Grew `Unk62044` (`unk24`), `Unk33F30` nested layout; added `Unk33A5C`/`Unk6A580`/`Unk0758`/`Unk62790Obj`; `sub_080330F4`/`6A3A4`/`62790` signatures aligned
- Near-miss: `sub_08061C48` (770 rematerialized vs r5), `sub_0806209C` (store 0 in r0 vs r1), `sub_0804745C` (630 in r6 vs r1 then copy)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+5)

- Semantic C: `sub_080679A4`/`679C0` (CpuSet to BG/OBJ palettes), `sub_080733BC` (append byte + NUL), `sub_080735B0` (walk pointer list via `73114`), `sub_08059C6C` (20 stride-`0x3C` slots)
- Grew `Unk047C` (`unk810[9]`); added `Unk59C6C`
- Near-miss: `sub_080447CC` (unk18 in r1 vs r0), `sub_0803DCFC` (index in r2 vs r1), `sub_0806105C` (counter vs string regs), `sub_08068884` (extra `lr`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_08035884` (Unk35878 range walk + optional `_08073C4C`), `sub_08036264` (midpoint + scaled distance via `674B0`), `sub_0806306C` (palette CpuSet + free IWRAM slots), `sub_0803EDF0` (byte at +3 on `Unk0C` stride-12), `sub_08072CC0` (free `unk10`), `sub_080720F0` (indexed `71EE4`)
- Grew `Unk346C0` (`unk08`/`unk2CC`/`unk2DC`/`unk2E0`/`unk2F8`/`unk2FC`/`unk30C`–`unk314`), `Unk0C` (`unk03`), `Unk312EC` (`s8 unk00/unk01`, `Unk705DC *unk0C`); added `Unk705DC`/`Unk36264`
- Near-miss: extra-`lr` leaves (`61BDC`/`62634`/`62728`/`33958`/`61E40`/`62684`/`6DEF4`/`6AC68`/`2D8C4`/`69F00`/`6BE08`/`35908`/`347E4`), pool-fold (`66434`/`66440`/`6644C`/`62A1C`/`473E4`), same-size (`44F64` muls vs shift-add, `42B28`/`42B50` index regs, `34A68` `0x314-0x1C` reuse, `31300` ldrsb else)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08032D5C` (stack pair into `unk2E4`/`unk2E8`, then `35054`/`628B4`/`3559C`/`60254`)
- `make compare`: **OK**

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

### 2026-09-19 — hand C convert (+1, 234/633 semantic)
- Function: `sub_0802C5DC` (battle Unk1694 find-and-mark lookup)
- make compare: OK
