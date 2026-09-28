# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-28T08:36:07Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 575 |
| Still need semantic C | **58** |
| Readable Thumb remaining | 58 |
| Opcode embeds remaining | 0 |
| Battle pending | 20 (138 already semantic) |
| Blocked (documented) | 20 |
| WIP (resume these first) | 31 |

Ranking: **battle** · showing top **40**

Park unmatched C in [`src/decompiled/`](../src/decompiled/README.md) — see [`decomp-wip.md`](decomp-wip.md).

## Resume (WIP)

_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._

| Function | Bytes | Score | Seed | Status | Next |
|----------|------:|-------|------|--------|------|
| `sub_0802BC14` | 0 | 5/112 | `src/decompiled/sub_0802BC14.c` | size_mismatch 5/112; u32 prototype, 60s permuter no score 0 | Do not re-attempt by hand or by permuter until a new seed exists. |
| `sub_080302E0` | 0 | compile-fail | `src/decompiled/sub_080302E0.c` | seed does not compile: Unk battle struct has no unk13C/unkAE8 | Do not re-attempt until those struct members exist. |
| `sub_08031C98` | 0 | 15/150 | `src/decompiled/sub_08031C98.c` | two semantic attempts: 43/150 size_mismatch (148B), then 15/150 size_mismatch (136B); control flow and record/counter roles are clear, but retail keeps r4-r7/state pointers and performs a byte-offset word read at IWRAM +0x18 that the current semantic shape does not reproduce | Use a targeted register-layout/permuter search; model the byte-offset word window without leaving raw offset casts in matched semantic C |
| `sub_08035624` | 114 | 20/114 | `src/decompiled/sub_08035624.c` | two attempts: 20/114 bytes, 112B candidate both times; logic and fields match, but agbcc omits retail's pushed r5/type-copy register and changes the prologue | Force a genuinely live selector copy in r5 or use a targeted source/permuter register search; preserve signed-byte delta and Unk705DC +0x22 |
| `sub_08038D68` | 112 | 37/112 | `src/decompiled/sub_08038D68.c` | two attempts: direct semantic seed 15/112 (108B); pinned base/table registers 37/112 but expanded to 120B. Data flow and both Unk705DC output writes are correct; register pressure/order remains | Use the direct field algorithm with a targeted r5 base/r2 table search; avoid the current over-constraining dual register pins and preserve the 112-byte retail size |
| `sub_080411EC` | 0 | 36/346 then 35/346 | `src/decompiled/sub_080411EC.c` | Two semantic attempts failed to preserve the retail dispatcher shape: direct struct logic 36/346 (332B), then r2 key pin plus volatile mode reload 35/346 (328B). The state pointer fields, two callback modes, key masks, and sub_08045C5C flag path are modeled. | Use the original direct seed with a targeted literal/register-order search: force a separate 0x2D9 offset pool load, keys in r1/r2, and preserve the callback fallthrough labels; avoid fixed pins that shrink the branch layout. |
| `sub_08045D3C` | 0 | 43/436 then 81/436 | `src/decompiled/sub_08045D3C.c` | Two attempts: readable semantic seed 43/436 (332B), then switch plus r2/r4/r3/r5 register pins 81/436 (364B). Packed low-byte group/bit semantics, global 8-word bit operations, table save/restore cases 0x3EA/0x3EB, and pointer save/restore cases 0x3EC/0x3ED are documented; initial mask temporary and branch/copy layout still differ. | Restore pinned switch semantics selectively: retain operation r3/output r5/group r2/bit r4, but force the 0xF8 mask through ordinary r1 (not bit's fixed r4); use a permuter for case dispatch and copy branches. |
| `sub_08045EF0` | 548 | 70/548 then 78/548 | `src/decompiled/sub_08045EF0.c` | Two attempts: semantic byte-state seed 70/548 (392B), then retail argument register pins 78/548 (404B). Operations are mapped for byte set/clear/increment/decrement/compare and table/pointer transfers at 0x3E8/0x3E9/0x3EE/0x3EF; remaining mismatch is switch branch layout, signed-byte loop generation, and copy expansion. | Restore the pinned argument layout; use a switch/source shape matching retail case ordering (10, 5-9, 0x3E8..), signed s8 loop counters, and explicit byte-array pointers to reproduce ldm/stm-style copies. |
| `sub_080474AC` | 0 | 24/232 then 25/232 | `src/decompiled/sub_080474AC.c` | Two semantic attempts: local pool physics seed 24/232 (200B), then r3-pinned MainWork 25/232 (200B). Behavior and pool-slot fields are mapped, but retail retains location/pointer registers and emits ldm-based 16-slot loops that the semantic array indexing does not reproduce. | Restore the baseline; use a targeted register/permuter search for MainWork r3, pool-location r4, pool pointer r2, and ldm/stm slot iteration while preserving 0x1825/0x1827 gates and random updates. |
| `sub_0805E044` | 0 | 16/228 then 15/228 | `src/decompiled/sub_0805E044.c` | Two semantic attempts: typed table-pointer loop 16/228 (212B), then explicit ROM-base plus offset loop 15/228 (224B). Direct resource cases and callback payload semantics are mapped; retail loop retains ROM base in r2, byte offset in r4, and index in r6, while semantic C allocation/layout differs. | Use targeted offset/register search: preserve resource in r5, ROM base 0x080991D0 in r2, byte offset r4, index r6; retain the three direct resource branches and shared sub_0802D8C4 tail. |
| `sub_08061564` | 0 | 11/136 then 9/136 | `src/decompiled/sub_08061564.c` | Two semantic attempts: switch-based C 11/136 (144B), then explicit branch/goto form 9/136 (148B). Existing matched file is retained as naked assembly. Semantic body is mapped; remaining codegen requires pinning input/cursor/opcode to retail r0/r4/r2, restoring direct unk92 += unkA2 for load order, and using switch cases 8/7 with default handling opcode 10 via inverted cmp. | Use a switch on opcode with only cases 8 and 7; in default, if opcode != 10 dispatch unknown, otherwise perform the Unk0798 update then fall through shared x/y draw. Pin input r0, cursor r4, opcode r2 if needed. |
| `sub_08062F90` | 148 | 19/148 then 33/148 | `src/decompiled/sub_08062F90.c` | Two attempts: direct global C 19/148 (144B), then e0/d4 lifetime anchors 33/148 (152B). Initialization semantics and both palette copies are mapped; remaining codegen is saved-register/lifetime shaping: retail keeps e0 location r5, d4 location r6, size r4, recomputes DC without retaining its address, then loads D8 location into r6; candidate retains DC via r8 and uses r7/r4 temporaries. | Make the DC guard/store volatile or otherwise recompute its address, pin the 0x200 size to r4, keep e0 r5/d4 r6, and use a separate D8 location variable loaded into r6 after storing the D4-derived pointer. Retain palette-table loading after that. |
| `sub_08067504` | 0 | 48/128 then 60/128 | `src/decompiled/sub_08067504.c` | Two semantic attempts: direct volatile-register C 48/128 (120B), then explicit waitcnt/mask temporaries 60/128 (112B). DMA behavior and register sequence are mapped; remaining issues are waitcnt result register (retail r4 = REG_WAITCNT & 0xF8FF, candidate r3) and DMA-status literal scheduling (retail loads 0x040000DE before constructing the r1 mask). | Pin waitcnt to r4 and the F8FF mask to r3, then OR in gUnk_030009B0->unk06. Introduce a DMA-status pointer pinned to r2 before setting busy_mask r1, and loop through that pointer. |
| `sub_08067648` | 352 | 50/352 then 50/352 | `src/decompiled/sub_08067648.c` | Two semantic attempts: approximate DMA/timing model 50/352 (260B), then enlarged scratch array still 50/352 (260B). The high-level stages are mapped, but the retail function’s fixed 0xB0 stack frame, bit-stream packing, DMA timing loop, and hardware-status branches require a dedicated stack-struct/source-shape match. | Use an explicit volatile 0xB0-byte workspace or struct to force the retail frame and model the exact scratch regions: stream at sp, VCOUNT fields at +0xA4/+0xA6/+0xA8, elapsed at +0xAC. Then anchor source r5, value r1/r3, mode r7, and cursor r3/r2 as shown by retail. |
| `sub_080691E4` | 0 | 15/138 then 20/138 | `src/decompiled/sub_080691E4.c` | Two semantic attempts: direct mode switch 15/138 (128B), then exact two-step value shift 20/138 (128B). Retail additionally copies value into r0, uses r0 for the bit-branch shift amount, and lays the non-bit cases as equality/value-greater-than checks (bgt plus explicit zero check); the candidate uses a compact switch and wrong register shape. | Pin selector to r0 and copy selector = value immediately after the >>30; in the bit path compute selector = (value << 1) + 8, result = one, result <<= selector. Replace switch with if value==1, else if value>1 using selector==2/3, else if value==0, leaving default result untouched. |
| `sub_0802DCDC` | 452 | 100/452 | `src/decompiled/sub_0802DCDC.c` | size mismatch; 100/452 bytes, compiled 428 vs retail 452; direct semantic control flow mapped, but frame remains 0x1C vs retail 0x18 and high-register lifetimes differ | reduce spills to the retail 0x18 frame, preserve r8/r9/r10 and exact state-location reloads |
| `sub_0802E2F8` | 0 | 4/110 | `src/decompiled/sub_0802E2F8.c` | two attempts did not match; 4/110 bytes, final pinned candidate 116B; table algorithm mapped but fixed-register aliases worsened the prologue | restore the 20/110 natural seed, then tune only multiplier r5, signed a r2, and table r3 without overlapping fixed variables |
| `sub_0802ECD8` | 0 | 50/498 | `src/decompiled/sub_0802ECD8.c` | two attempts did not match; 50/498 bytes, final compiled 416B; logic mapped but fixed high-register pins removed the retail callee-save prologue | restore natural prologue from first seed, then selectively anchor buffer/index/root location without fixed r8-r10 pins |
| `sub_0802FA94` | 0 | 65/748 | `src/decompiled/sub_0802FA94.c` | two attempts did not match; 65/748 bytes, final compiled 580B; loop semantics mapped but target root/main location and high-register/dispatch shape remain | restore natural callee-save prologue and use a root-location direct seed; inline the exact type/subtype switch and table literal order |
| `sub_08030F38` | 348 | 54/348 | `src/decompiled/sub_08030F38.c` | Resource timer/update semantics reconstructed across the AF0/B00/B20/B40/B48 paths, but two compiler attempts diverged in prologue and pointer scheduling (376-byte candidate versus 348-byte target). | Use the target's callee-save shape: seed gBattleWorkPtrLoc in r7, retain the initial work pointer in r4 only through the AF* updates, then hand-write scoped register aliases for the B00/B20 loop and final B48 delta clamp. |
| `sub_0803114C` | 0 | 13/184 | `src/decompiled/sub_0803114C.c` | Entry-position initialization semantics reconstructed with both direction branches and resource rebinding, but compiler output remains 156/184 bytes after two attempts. | Pin the base argument in r8 and preserve the original duplicated loop setup; target keeps separate mode-zero/nonzero loops, count in r6, remaining in r5, and reloads gBattleWork->unkBB0 per entry. |
| `sub_08033188` | 0 | 63/604 | `src/decompiled/sub_08033188.c` | Input-transition routine semantics mapped (input snapshot/restore, two-frame asset save/restore, transition loop, and final cleanup), but two compiler candidates diverged substantially; best baseline was 63/604 bytes. | Use the baseline without fixed r8/r9/r10 locals; model the input snapshots as stack-resident u16s and use a dedicated state object matching the Unk7069C layout before tuning the two asset-copy loops. |
| `sub_0803370C` | 0 | 21/362 | `src/decompiled/sub_0803370C.c` | Battle animation-position update semantics reconstructed (timer/counter, resource digit allocation, position interpolation, and branch-specific endpoint sampling), but candidate remains 21/362 bytes after two attempts. | Recover the target's duplicated register-driven loops: retain gBattleWork pointer in r3/r6, use direct B54/B74/B7C aliases, and preserve separate B00/B20 sub_08031368 blocks. |
| `sub_08035054` | 432 | 80/432 | `src/decompiled/sub_08035054.c` | Rewritten seed (old_agbcc, u16 id local, data symbols) is structurally exact; only register allocation differs: retail src=r7, pos=r8, ours pos=r7, src=r8, which costs 8B (mov via r8). Permuter best 301 (376/432 same-size) only by dropping the src=NULL init. | Find the source shape that gives src higher global-alloc priority than pos (decl/init order sweeps, u8 params and else-NULL all failed). |
| `sub_08035D68` | 0 | 19/196 | `src/decompiled/sub_08035D68.c` | Rotation/projection helper semantics reconstructed: table sine/cosine lookup, depth-scaled coordinate rotation, perspective correction, output writes, flag extraction, and sub_08070354 dispatch. Natural baseline is 19/196 bytes and size-mismatched at 208 bytes; a second fixed-register attempt reached 50/196 but aliased the source pointer with a pinned delta and was discarded. | Use the natural seed and introduce register constraints only after preserving the source pointer in ip. Target uses sine r8, dx r7, dy r5, dz r4, output x r6, output y r2, and flag r9; do not pin dx to r7 unless source is explicitly pinned to r12. |
| `sub_0803715C` | 0 | 33/444 | `src/decompiled/sub_0803715C.c` | 33/444 size mismatch (424 vs 444); algorithm transcribed, a is kept in r4 instead of r8 and about 20 bytes of reloads are folded | do not hand-chase registers; only revisit if a same-size seed appears, then permuter |
| `sub_08038438` | 240 | 45/240 | `src/decompiled/sub_08038438.c` | for-loop seed with slots=&gData_030003CC + _call_via_r3 fn-pointer call is same-size (old_agbcc 45/240). Retail keeps both loops' found-blocks inline (no loop-exit block motion), so *slots reloads every pass; agbcc/old_agbcc move the found blocks out of the loops. | Find a loop shape that stops loop.c moving the exit blocks (break + flag, goto-free) while keeping the hoisted r7/r8/r5 in loop 2. |
| `sub_08045C5C` | 136 | 93/136 | `src/decompiled/sub_08045C5C.c` | Same-size semantic seed 93/136; permuter best 255 in 60s. Retail keeps a in r7 and builds 0xFC00 in r1 before copying the mask pointer; agbcc puts a in r6, the constant in r2, and swaps the mask copy with the halfword load. | Need a in r7 and sentinel in r1 so the mask pointer is copied before the halfword load. Do not re-run this seed until that register shape exists. |
| `sub_08069270` | 244 | 24/244 | `src/decompiled/sub_08069270.c` | Logic mapped (horizontal wrap split into two blits; fn = 0x0806945D or gData_080BB8A4[0]; wrap-off path uses gData_080BB8A8[0]). Separate e1/e2/h1/h2 copies reproduce retail's stack spills; remaining diff is register choice: retail keeps d in r3 and end in r5, ours copies d to r6 (+2B). Permuter (2 rounds) reached 25 only via uninitialised-variable tricks. | Find a source shape that leaves d in its argument register (d is only read by the first blit); try the permuter from this seed with a longer budget. |
| `sub_0806B2F0` | 248 | 35/248 | `src/decompiled/sub_0806B2F0.c` | Digit-row renderer (right to left, DivRemainder/Div by 10, frame 0x34 + digit, optional zero padding). Our compile cross-jumps the two sub_0806833C calls; retail keeps them separate because the padded path increments from the (s16)drawn value it just tested. | Make the padded-path increment differ from the normal path (retail: drawn = (s16)drawn + 1 vs drawn++), and keep i/drawn as u16 compared via (s16). |
| `sub_0806B5C8` | 274 | 87/274 | `src/decompiled/sub_0806B5C8.c` | 8x8 4bpp glyph blit into a 2x2 tile block (tiles[0,1,0x20,0x21] via sub_0806B5B8), shifted by x&7 and y&7. Logic complete; register allocation differs (retail: base/br share r7, x reused as the shift in r9, y&7 in r10, first row count as ~y + 8). | Reuse x for the shift and y for the second loop's counter; try n = 7 - y with != -1 tests; then permuter. |

Per-function notes: `src/decompiled/<fn>.md`.

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_08046E7C` | `0x08046E7C` | 872 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_0806F910` | `0x0806F910` | 624 | 2 | pool | asm | (gBtlObjListHead, gBtlObjListTail) |
| `sub_0803E0CC` | `0x0803E0CC` | 296 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08040680` | `0x08040680` | 308 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08065CD0` | `0x08065CD0` | 316 | 1 | pool | asm | (gBattlerArena/gBtlKeysHeld) |
| `sub_08043C70` | `0x08043C70` | 324 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08044648` | `0x08044648` | 364 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080447E8` | `0x080447E8` | 372 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080618EC` | `0x080618EC` | 428 | 1 | pool | asm | (gBtlInputMask) |
| `sub_08056BA4` | `0x08056BA4` | 450 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08053690` | `0x08053690` | 528 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08054120` | `0x08054120` | 594 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08044A8C` | `0x08044A8C` | 672 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08045198` | `0x08045198` | 1016 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08045590` | `0x08045590` | 1256 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08043DB4` | `0x08043DB4` | 1352 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0804FFCC` | `0x0804FFCC` | 1504 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0806F05C` | `0x0806F05C` | 280 | 0 | pool | asm | |
| `sub_08069A60` | `0x08069A60` | 280 | 0 | pool | asm | |
| `sub_0806211C` | `0x0806211C` | 284 | 0 |      | asm | |
| `sub_0804AE94` | `0x0804AE94` | 300 | 0 | pool | asm | |
| `sub_08056250` | `0x08056250` | 302 | 0 | pool | asm | |
| `sub_0804BD38` | `0x0804BD38` | 328 | 0 | pool | asm | |
| `sub_08061EF8` | `0x08061EF8` | 332 | 0 | pool | asm | |
| `sub_080737C0` | `0x080737C0` | 336 | 0 | pool | asm | |
| `sub_0804D420` | `0x0804D420` | 362 | 0 | pool | asm | |
| `sub_0804C8BC` | `0x0804C8BC` | 372 | 0 | pool | asm | |
| `sub_0806314C` | `0x0806314C` | 404 | 0 | pool | asm | |
| `sub_0806EEC8` | `0x0806EEC8` | 404 | 0 | pool | asm | |
| `sub_08070AF8` | `0x08070AF8` | 416 | 0 | pool | asm | |
| `sub_08068BD4` | `0x08068BD4` | 420 | 0 | pool | asm | |
| `sub_08070930` | `0x08070930` | 420 | 0 | pool | asm | |
| `sub_08048DB8` | `0x08048DB8` | 440 | 0 | pool | asm | |
| `sub_08068A08` | `0x08068A08` | 460 | 0 | pool | asm | |
| `sub_0806E060` | `0x0806E060` | 492 | 0 | pool | asm | |
| `sub_0806EC20` | `0x0806EC20` | 516 | 0 | pool | asm | |
| `sub_08060E48` | `0x08060E48` | 532 | 0 | pool | asm | |
| `sub_08067CE8` | `0x08067CE8` | 548 | 0 | pool | asm | |
| `sub_0806B764` | `0x0806B764` | 588 | 0 | pool | asm | |
| `sub_0806960C` | `0x0806960C` | 600 | 0 |      | asm | |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802C62C` | `0x0802C62C` | 0 | counts gMainWorkPtr->unk1694[0..0x7F] entries with unk03==(s8)a — same-size DIFF (64B=64B!) across every declaration-order variant tried, purely a r2/r3/r4 register-choice swap (which var lands in the return register); 7000+ permuter iterations floor at score 95, never zero; needs permuter |
| `sub_08030938` | `0x08030938` | 0 | computes a->unk2D8/unk2D4/unk00->unk30/unk00->unk34/nested sub_080674A0 fixed-point calls, then sub_080346C0(a, unk30, unk34, unk2D8, 0xB4-nested) with 5th arg on stack — logic correct across several forms but push-set (r4-r7 vs r4-r6) and stack-arg store ordering differ; needs permuter |
| `sub_08033530` | `0x08033530` | 0 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_08034894` | `0x08034894` | 0 | docs/battle.md: readable Thumb — agbcc prologue / pool ordering (no struct yet for param @ +0x30C flag / +0x300,0x302,0x304 fields) |
| `sub_08038314` | `0x08038314` | 0 | battle countdown gate: a->unk304-- then flush-condition on gBtlKeysHeld&3, else store v to a->unk2FC and sub_08062044 x4 on gBattleWork->unk19C[0..3] — logic reconstructed correctly (same-size DIFF, 5/108 bytes), several source shapes (inline expr, cached local, array-index cast) all land agbcc on the same reordering (mask loaded+ANDed before vs after the #3 immediate load); needs permuter (base score 70, 20k+ iterations without a zero) |
| `sub_080428C4` | `0x080428C4` | 0 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_08045C5C` | `0x08045C5C` | 136 | gMainWorkPtr->unk1710[25..26] input-repeat debouncer keyed on gBtlInputMask==0xFC00 — logic reconstructed correctly but agbcc drops r7 from the push set (r4-r6+lr, 140B) vs retail's r4-r7+lr (136B); tried inline/cached-local/branch-order variants, all land on the same 4B-over shape; needs permuter |
| `sub_080473E4` | `0x080473E4` | 0 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_08049F98` | `0x08049F98` | 0 | sound/anim trigger sequencer: sub_080617C4 x2, sub_080615EC x3 with idx<<4+8/+0x10 offsets, sub_0806171C x3 with sub_08061784()<<16>>17 — m2c fails to reconstruct (r8 stack-saved 3rd param); multiple hand-written + register-pinned C forms all land 8 bytes over; needs permuter |
| `sub_0804E17C` | `0x0804E17C` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A83F4); same blocker |
| `sub_08051578` | `0x08051578` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A85A4); same blocker |
| `sub_08053218` | `0x08053218` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A8724); same blocker |
| `sub_080601C4` | `0x080601C4` | 0 | r8 pool pin — permuter best score ~100 |
| `sub_080604C8` | `0x080604C8` | 0 | byte-swaps 6 u8 pairs from *gUnk_03000750 into u16 fields, writes them to REG_BG palette-ish IO regs 0x04000040-0x0400004A — logic correct; real remaining gap is a 4-byte tail-fold (agbcc collapses the last out=out+2;*out=val into strh [r0,#2] when out isn't used again, unlike retail which keeps the explicit adds+strh[0]); several dependency-shape rewrites (loop, pre-increment, reordering) all land 4B short; needs permuter |
| `sub_08062728` | `0x08062728` | 0 | u32 zero-fill loop (a->unk04[i]=0 for i<a->unk08) — retail uses stm r0!,{r3} leaf loop (18B), agbcc compiles any equivalent C to a push/pop-framed indexed loop (32B); needs permuter or specific idiom to trigger stm codegen |
| `sub_08062C80` | `0x08062C80` | 0 | calls _08073C4C(0, dst, size, src) at raw address 0x08073C4C twice (VRAM/PLTT clear via CpuFastSet-style primitive) — that callee has no C symbol/prototype anywhere in the codebase yet (only referenced via bl _08073C4C from naked asm in many other unconverted functions); needs the callee named/prototyped first |
| `sub_08062CF4` | `0x08062CF4` | 0 | BGR555 color pack (inverse of sub_08062CC8/sub_08062D24): rgb[0..2] -> u16 @ PLTT 0x05000200+idx*2 — logic reconstructed correctly (same-size DIFF, ~1 instruction reordered) across many register-pinned variants; retail keeps r6 live (push {r4,r5,r6,lr}) but my C never needed r6 pressure, changing push set; needs permuter |
| `sub_0806A6F8` | `0x0806A6F8` | 436 | docs/battle.md: readable Thumb — large input hub (436B, 6 IWRAM refs) |
| `sub_08073114` | `0x08073114` | 0 | BtlObjTable scan+remove (loop over gBtlObjTable[0..gBtlObjTableCount) matching entry->key==obj, calls sub_0806A434/sub_08067B98) — logic reconstructed correctly (same-size DIFF on every variant tried) but agbcc compiles the do-while as pre-test loop + different table-pointer register placement than retail; needs permuter or deeper agbcc loop-codegen trick |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c --status "…" --next "…"
python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/function_scores.py --close
python3 tools/decomp/script_first.py
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/cluster_shapes.py
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
```

Full ranked backlog (43 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
