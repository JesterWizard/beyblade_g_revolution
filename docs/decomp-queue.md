# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-18T20:41:50Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 182 |
| Still need semantic C | **451** |
| Readable Thumb remaining | 448 |
| Opcode embeds remaining | 3 |
| Battle pending | 143 (15 already semantic) |
| Blocked (documented) | 8 |

Ranking: **battle** · showing top **40**

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_0806A6F8` | `0x0806A6F8` | 436 | 6 | pool | asm | (gBtlInputMask, gBtlState, gBattlerArena/gBtlKeys) — Battle input / key queue (6 IWRAM refs, large) |
| `sub_08034894` | `0x08034894` | 84 | 3 | pool | asm | (gBtlInputMask, gBattlerArena/gBtlKeysHeld, gBtlK) — Small battle input helper (3 refs, 32B score) |
| `sub_08033188` | `0x08033188` | 604 | 5 | pool | asm | (gMainWorkPtr, gBattleWork, gBtlInputMask, gBattl) |
| `sub_08073114` | `0x08073114` | 112 | 3 | pool | asm | (gBtlObjTable, gBtlObjTableCount, gBtlObjLiveCoun) |
| `sub_0807309C` | `0x0807309C` | 120 | 3 | pool | asm | (gBtlObjTable, gBtlObjTableCount, gBtlObjLiveCoun) |
| `sub_080436B0` | `0x080436B0` | 658 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08046E7C` | `0x08046E7C` | 872 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_0806FEFC` | `0x0806FEFC` | 44 | 2 | pool | asm | (gBtlObjListHead, gBtlObjListTail) |
| `sub_0806FF28` | `0x0806FF28` | 48 | 2 | pool | asm | (gBtlObjListHead, gBtlObjListTail) |
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
| `sub_0803DD60` | `0x0803DD60` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803EBB0` | `0x0803EBB0` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803EC34` | `0x0803EC34` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803ECB8` | `0x0803ECB8` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042B00` | `0x08042B00` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803DD88` | `0x0803DD88` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803DDB0` | `0x0803DDB0` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803DDD8` | `0x0803DDD8` | 40 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080428C4` | `0x080428C4` | 44 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080475C4` | `0x080475C4` | 48 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080475F4` | `0x080475F4` | 48 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08043B58` | `0x08043B58` | 54 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802B994` | `0x0802B994` | 58 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0804495C` | `0x0804495C` | 60 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C62C` | `0x0802C62C` | 64 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803FDD0` | `0x0803FDD0` | 64 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080330F4` | `0x080330F4` | 72 | 1 | pool | asm | (gBattleWork) |
| `sub_08046230` | `0x08046230` | 72 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08052FC8` | `0x08052FC8` | 72 | 1 | pool | asm | (gMainWorkPtr) |

## Pinned (manual)

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_0806A6F8` | `0x0806A6F8` | 436 | 6 | pool | asm | (gBtlInputMask, gBtlState, gBattlerArena/gBtlKeys) — Battle input / key queue (6 IWRAM refs, large) |
| `sub_08034894` | `0x08034894` | 84 | 3 | pool | asm | (gBtlInputMask, gBattlerArena/gBtlKeysHeld, gBtlK) — Small battle input helper (3 refs, 32B score) |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802D8C4` | `0x0802D8C4` | 24 | agbcc extra push {lr} on branch leaves |
| `sub_08033530` | `0x08033530` | 68 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_080473E4` | `0x080473E4` | 20 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_080601C4` | `0x080601C4` | 92 | r8 pool pin — permuter best score ~100 |
| `sub_080615EC` | `0x080615EC` | 36 | branchy asm — agbcc compile fail |
| `sub_08061BDC` | `0x08061BDC` | 12 | agbcc extra push {lr} on null-check leaf |
| `sub_08061E40` | `0x08061E40` | 20 | agbcc extra push {lr} on null-check leaf |
| `sub_08062634` | `0x08062634` | 12 | agbcc extra push {lr} on null-check leaf |

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

Full ranked backlog (443 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
