# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-19T13:03:24Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 231 |
| Still need semantic C | **402** |
| Readable Thumb remaining | 402 |
| Opcode embeds remaining | 0 |
| Battle pending | 110 (33 already semantic) |
| Blocked (documented) | 35 |

Ranking: **battle** · showing top **40**

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_08033188` | `0x08033188` | 604 | 5 | pool | asm | (gMainWorkPtr, gBattleWork, gBtlInputMask, gBattl) |
| `sub_0807309C` | `0x0807309C` | 120 | 3 | pool | asm | (gBtlObjTable, gBtlObjTableCount, gBtlObjLiveCoun) |
| `sub_080436B0` | `0x080436B0` | 658 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08046E7C` | `0x08046E7C` | 872 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08037430` | `0x08037430` | 216 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803C5DC` | `0x0803C5DC` | 220 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803C500` | `0x0803C500` | 220 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08036A68` | `0x08036A68` | 240 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803D51C` | `0x0803D51C` | 304 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08038F30` | `0x08038F30` | 316 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08032908` | `0x08032908` | 384 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08037508` | `0x08037508` | 452 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0806F910` | `0x0806F910` | 624 | 2 | pool | asm | (gBtlObjListHead, gBtlObjListTail) |
| `sub_08032DC4` | `0x08032DC4` | 660 | 2 | pool | asm | (gBattleWork, gBattlerArena/gBtlKeysHeld) |
| `sub_08043B58` | `0x08043B58` | 54 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803FDD0` | `0x0803FDD0` | 64 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08052FC8` | `0x08052FC8` | 72 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08043B90` | `0x08043B90` | 76 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C5DC` | `0x0802C5DC` | 78 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033574` | `0x08033574` | 80 | 1 | pool | asm | (gBattleWork) |
| `sub_08052934` | `0x08052934` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0805D99C` | `0x0805D99C` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080424E8` | `0x080424E8` | 88 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08040EF4` | `0x08040EF4` | 88 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803D4C4` | `0x0803D4C4` | 88 | 1 | pool | asm | (gBattleWork) |
| `sub_080449C4` | `0x080449C4` | 92 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08046278` | `0x08046278` | 92 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042390` | `0x08042390` | 98 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033084` | `0x08033084` | 100 | 1 | pool | asm | (gBattleWork) |
| `sub_08042784` | `0x08042784` | 100 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C2B0` | `0x0802C2B0` | 100 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802D52C` | `0x0802D52C` | 108 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033878` | `0x08033878` | 108 | 1 | pool | asm | (gBattleWork) |
| `sub_08042718` | `0x08042718` | 108 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802D2C0` | `0x0802D2C0` | 108 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802BC14` | `0x0802BC14` | 112 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042630` | `0x08042630` | 116 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080426A4` | `0x080426A4` | 116 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080392D0` | `0x080392D0` | 116 | 1 | pool | asm | (gBattleWork) |
| `sub_08042540` | `0x08042540` | 120 | 1 | pool | asm | (gMainWorkPtr) |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802B994` | `0x0802B994` | 58 | Unk7709C ROM table lookup keyed on *gMainWorkPtr->unk1690 — logic reconstructed correctly (same-size DIFF, 2/58 bytes short from a missing 2B) but every do/while/goto shape tried lands agbcc on push{lr}...pop{r1};bx r1 leaf framing that retail doesn't have (bx lr direct); same agbcc-extra-push-on-leaf class as sub_0802D8C4/sub_08061BDC; needs permuter |
| `sub_0802C62C` | `0x0802C62C` | 64 | counts gMainWorkPtr->unk1694[0..0x7F] entries with unk03==(s8)a — same-size DIFF (64B=64B!) across every declaration-order variant tried, purely a r2/r3/r4 register-choice swap (which var lands in the return register); 7000+ permuter iterations floor at score 95, never zero; needs permuter |
| `sub_0802D8C4` | `0x0802D8C4` | 24 | agbcc extra push {lr} on branch leaves |
| `sub_08030938` | `0x08030938` | 78 | computes a->unk2D8/unk2D4/unk00->unk30/unk00->unk34/nested sub_080674A0 fixed-point calls, then sub_080346C0(a, unk30, unk34, unk2D8, 0xB4-nested) with 5th arg on stack — logic correct across several forms but push-set (r4-r7 vs r4-r6) and stack-arg store ordering differ; needs permuter |
| `sub_08033530` | `0x08033530` | 68 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_08034894` | `0x08034894` | 84 | docs/battle.md: readable Thumb — agbcc prologue / pool ordering (no struct yet for param @ +0x30C flag / +0x300,0x302,0x304 fields) |
| `sub_08038314` | `0x08038314` | 108 | battle countdown gate: a->unk304-- then flush-condition on gBtlKeysHeld&3, else store v to a->unk2FC and sub_08062044 x4 on gBattleWork->unk19C[0..3] — logic reconstructed correctly (same-size DIFF, 5/108 bytes), several source shapes (inline expr, cached local, array-index cast) all land agbcc on the same reordering (mask loaded+ANDed before vs after the #3 immediate load); needs permuter (base score 70, 20k+ iterations without a zero) |
| `sub_0803DBD0` | `0x0803DBD0` | 80 | 2D ROM table lookup (gUnk_080796DC[a][gMainWorkPtr->unk1818] / gUnk_08097458[unk1818] fallback) — retail leaf is bx lr with no push at all; every C shape tried (both branch orders) needs push{lr}/pop{r1} for one extra temp register (80B retail vs 84B compiled); same agbcc-extra-push-on-leaf class; needs permuter |
| `sub_080428C4` | `0x080428C4` | 44 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_0804495C` | `0x0804495C` | 60 | 32-halfword table copy (gUnk_08094E00[gMainWorkPtr->unk181F] -> PLTT 0x050001C0) — void(void) leaf, same agbcc-extra-push-on-leaf framing as sub_0802B994 (60B retail vs 64B compiled, same shape every C form tried); needs permuter |
| `sub_08045128` | `0x08045128` | 80 | reads gMainWorkPtr->unk1688[idx].unk08 into unk1788, computes base = gMainWorkPtr->unk168C + idx*8032 (retail's literal shift/sub chain), calls sub_08045590(base,0) — logic correct (same-size DIFF, ~14/80 bytes differ) across many pointer-arithmetic orderings tried; needs permuter for the base-pointer scheduling |
| `sub_08045C5C` | `0x08045C5C` | 136 | gMainWorkPtr->unk1710[25..26] input-repeat debouncer keyed on gBtlInputMask==0xFC00 — logic reconstructed correctly but agbcc drops r7 from the push set (r4-r6+lr, 140B) vs retail's r4-r7+lr (136B); tried inline/cached-local/branch-order variants, all land on the same 4B-over shape; needs permuter |
| `sub_080473E4` | `0x080473E4` | 20 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_080475C4` | `0x080475C4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_080475F4` | `0x080475F4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_08049F98` | `0x08049F98` | 144 | sound/anim trigger sequencer: sub_080617C4 x2, sub_080615EC x3 with idx<<4+8/+0x10 offsets, sub_0806171C x3 with sub_08061784()<<16>>17 — m2c fails to reconstruct (r8 stack-saved 3rd param); multiple hand-written + register-pinned C forms all land 8 bytes over; needs permuter |
| `sub_0804E17C` | `0x0804E17C` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A83F4); same blocker |
| `sub_08051578` | `0x08051578` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A85A4); same blocker |
| `sub_080523A4` | `0x080523A4` | 112 | calls sub_08061BE8, sub_0805264C(a,0..5), then a->unk288->unk0C = a->unk28C->unk0C = (a->unk2D5<<12)+0x2C00 — logic correct (same-size DIFF, ~15/112 bytes) across several pointer/base-register orderings; needs permuter |
| `sub_08053218` | `0x08053218` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A8724); same blocker |
| `sub_080601C4` | `0x080601C4` | 92 | r8 pool pin — permuter best score ~100 |
| `sub_080604C8` | `0x080604C8` | 112 | byte-swaps 6 u8 pairs from *gUnk_03000750 into u16 fields, writes them to REG_BG palette-ish IO regs 0x04000040-0x0400004A — logic correct; real remaining gap is a 4-byte tail-fold (agbcc collapses the last out=out+2;*out=val into strh [r0,#2] when out isn't used again, unlike retail which keeps the explicit adds+strh[0]); several dependency-shape rewrites (loop, pre-increment, reordering) all land 4B short; needs permuter |
| `sub_080615EC` | `0x080615EC` | 36 | branchy asm — agbcc compile fail |
| `sub_08061BDC` | `0x08061BDC` | 12 | agbcc extra push {lr} on null-check leaf |
| `sub_08061E40` | `0x08061E40` | 20 | agbcc extra push {lr} on null-check leaf |
| `sub_08062634` | `0x08062634` | 12 | agbcc extra push {lr} on null-check leaf |
| `sub_08062728` | `0x08062728` | 18 | u32 zero-fill loop (a->unk04[i]=0 for i<a->unk08) — retail uses stm r0!,{r3} leaf loop (18B), agbcc compiles any equivalent C to a push/pop-framed indexed loop (32B); needs permuter or specific idiom to trigger stm codegen |
| `sub_08062C80` | `0x08062C80` | 72 | calls _08073C4C(0, dst, size, src) at raw address 0x08073C4C twice (VRAM/PLTT clear via CpuFastSet-style primitive) — that callee has no C symbol/prototype anywhere in the codebase yet (only referenced via bl _08073C4C from naked asm in many other unconverted functions); needs the callee named/prototyped first |
| `sub_08062CF4` | `0x08062CF4` | 48 | BGR555 color pack (inverse of sub_08062CC8/sub_08062D24): rgb[0..2] -> u16 @ PLTT 0x05000200+idx*2 — logic reconstructed correctly (same-size DIFF, ~1 instruction reordered) across many register-pinned variants; retail keeps r6 live (push {r4,r5,r6,lr}) but my C never needed r6 pressure, changing push set; needs permuter |
| `sub_0806A6F8` | `0x0806A6F8` | 436 | docs/battle.md: readable Thumb — large input hub (436B, 6 IWRAM refs) |
| `sub_0806FEFC` | `0x0806FEFC` | 44 | BtlObjNode move-to-tail (gBtlObjListHead/Tail) — agbcc inserts extra push {lr}/pop{r1}+bx r1 frame on this null-check leaf like sub_0802D8C4/sub_08061BDC; same-size DIFF on direct-return form, +12B with early-return form; needs permuter |
| `sub_0806FF28` | `0x0806FF28` | 48 | BtlObj unlink+push-to-head (obj->unk19 early return) — same agbcc extra push{lr} frame quirk as sub_0806FEFC; +4B DIFF; needs permuter |
| `sub_08070604` | `0x08070604` | 92 | struct Unk70604 initializer (7 params, 3 via stack) — logic reconstructed correctly (m2c-verified, same overall shape) but agbcc's final two byte-field writes (unk29=0, unk2A=src->unk05+4) either share one address computation (too small, -4B) or use two fully separate ones (too big, +4B); retail shares the unk29 address computation only for unk2A, not unk28; needs permuter |
| `sub_08073114` | `0x08073114` | 112 | BtlObjTable scan+remove (loop over gBtlObjTable[0..gBtlObjTableCount) matching entry->key==obj, calls sub_0806A434/sub_08067B98) — logic reconstructed correctly (same-size DIFF on every variant tried) but agbcc compiles the do-while as pre-test loop + different table-pointer register placement than retail; needs permuter or deeper agbcc loop-codegen trick |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/function_scores.py --close
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
tools/decomp/battle_semantic_batch.sh 10
tools/decomp/semantic_convert_batch.sh 30 --pool-free-only
```

Full ranked backlog (367 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
