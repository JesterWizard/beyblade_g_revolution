# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-18T22:18:53Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 200 |
| Still need semantic C | **433** |
| Readable Thumb remaining | 433 |
| Opcode embeds remaining | 0 |
| Battle pending | 126 (23 already semantic) |
| Blocked (documented) | 21 |

Ranking: **battle** · showing top **40**

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_08033188` | `0x08033188` | 604 | 5 | pool | asm | (gMainWorkPtr, gBattleWork, gBtlInputMask, gBattl) |
| `sub_0807309C` | `0x0807309C` | 120 | 3 | pool | asm | (gBtlObjTable, gBtlObjTableCount, gBtlObjLiveCoun) |
| `sub_080436B0` | `0x080436B0` | 658 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08046E7C` | `0x08046E7C` | 872 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08038314` | `0x08038314` | 108 | 2 | pool | asm | (gBattleWork, gBattlerArena/gBtlKeysHeld) |
| `sub_08045C5C` | `0x08045C5C` | 136 | 2 | pool | asm | (gMainWorkPtr, gBtlInputMask) |
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
| `sub_0802B994` | `0x0802B994` | 58 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0804495C` | `0x0804495C` | 60 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C62C` | `0x0802C62C` | 64 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803FDD0` | `0x0803FDD0` | 64 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080330F4` | `0x080330F4` | 72 | 1 | pool | asm | (gBattleWork) |
| `sub_08046230` | `0x08046230` | 72 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08052FC8` | `0x08052FC8` | 72 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08043B90` | `0x08043B90` | 76 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C5DC` | `0x0802C5DC` | 78 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803DBD0` | `0x0803DBD0` | 80 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033574` | `0x08033574` | 80 | 1 | pool | asm | (gBattleWork) |
| `sub_0803E258` | `0x0803E258` | 82 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08041F88` | `0x08041F88` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08052934` | `0x08052934` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0805D99C` | `0x0805D99C` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08038D10` | `0x08038D10` | 86 | 1 | pool | asm | (gBattleWork) |
| `sub_080424E8` | `0x080424E8` | 88 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08040EF4` | `0x08040EF4` | 88 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803D4C4` | `0x0803D4C4` | 88 | 1 | pool | asm | (gBattleWork) |
| `sub_080449C4` | `0x080449C4` | 92 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08046278` | `0x08046278` | 92 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080435D8` | `0x080435D8` | 96 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C6AC` | `0x0802C6AC` | 96 | 1 | pool | asm | (gMainWorkPtr) |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802D8C4` | `0x0802D8C4` | 24 | agbcc extra push {lr} on branch leaves |
| `sub_08033530` | `0x08033530` | 68 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_08034894` | `0x08034894` | 84 | docs/battle.md: readable Thumb — agbcc prologue / pool ordering (no struct yet for param @ +0x30C flag / +0x300,0x302,0x304 fields) |
| `sub_080428C4` | `0x080428C4` | 44 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_08045128` | `0x08045128` | 80 | reads gMainWorkPtr->unk1688[idx].unk08 into unk1788, computes base = gMainWorkPtr->unk168C + idx*8032 (retail's literal shift/sub chain), calls sub_08045590(base,0) — logic correct (same-size DIFF, ~14/80 bytes differ) across many pointer-arithmetic orderings tried; needs permuter for the base-pointer scheduling |
| `sub_080473E4` | `0x080473E4` | 20 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_080475C4` | `0x080475C4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_080475F4` | `0x080475F4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_080601C4` | `0x080601C4` | 92 | r8 pool pin — permuter best score ~100 |
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
| `sub_08073114` | `0x08073114` | 112 | BtlObjTable scan+remove (loop over gBtlObjTable[0..gBtlObjTableCount) matching entry->key==obj, calls sub_0806A434/sub_08067B98) — logic reconstructed correctly (same-size DIFF on every variant tried) but agbcc compiles the do-while as pre-test loop + different table-pointer register placement than retail; needs permuter or deeper agbcc loop-codegen trick |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
tools/decomp/battle_semantic_batch.sh 10
tools/decomp/semantic_convert_batch.sh 30 --pool-free-only
```

Full ranked backlog (412 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
