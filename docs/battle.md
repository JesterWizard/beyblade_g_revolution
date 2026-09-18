# Battle subsystem (decomp notes)

_Agent-maintained. RAM names live in `asm/ram_map_iwram.s` / `include/battle.h`._

## IWRAM map (provisional)

| Symbol | Address | Role |
|--------|---------|------|
| `gMainWorkPtr` | `0x03000198` | Pointer to root main-work arena (`struct MainWork`) |
| `gBattleWork` | `0x03000290` | Pointer to battle work block (`sub_0803C500`) |
| `gBtlInputMask` | `0x03003F60` | Input mask (`sub_08034894`, `sub_0806A6F8`) |
| `gBtlState` | `0x03003F64` | Battle state phase (`sub_0806A6F8`) |
| `gBtlKeysHeld` / `gBattlerArena` | `0x03004060` | Held keys / arena base |
| `gBtlKeysNew` | `0x0300406C` | New key flags |
| `gBtlKeyQueuePtr` | `0x03004070` | Key queue cursor |
| `gBtlKeyQueueCount` | `0x03004074` | Key queue length |
| `gBtlObjListHead` | `0x030040A8` | Battle object freelist head |
| `gBtlObjListTail` | `0x030040B8` | Battle object freelist tail |
| `gBtlObjTable` | `0x03004150` | Battle object pointer table |
| `gBtlObjTableCount` | `0x03004154` | Table capacity |
| `gBtlObjLiveCount` | `0x03004158` | Live object count |
| `gBtlLookupBase` | `0x03004130` | Data lookup offset (`sub_08072F94`) |
| `gBtlLookupPtr` | `0x03004148` | Data lookup base pointer |

## Anchor functions

| Function | Notes |
|----------|-------|
| `sub_0806A6F8` | Battle input / key queue (large) |
| `sub_08034894` | Copies global key state into battle entity |
| `sub_0803C500` | Battle UI setup (`gBattleWork`) |
| `sub_08065CD0` | Battle scene driver |
| `sub_0807309C` / `sub_08073114` | Battle object table alloc / remove |
| `sub_080628E4` | Write `gMainWorkPtr->unk1800` (semantic C) |
| `sub_080628B4` | LCG step on `unk1800`, then `_08074264` (semantic C) |
| `sub_080433F4` | Clear `unk1834`, drop bit 9 of `unk1808` (semantic C) |

## `MainWork` fields used in battle C

| Offset | Member | Role |
|--------|--------|------|
| `+0x0874` | `unk0874` | `s16` thunk arg (`sub_0802E1EC`) |
| `+0x15C8`–`+0x15D2` | `unk15C8`–`unk15D2` | `s8` flags / `s16` pair (`sub_0802C6AC`) |
| `+0x1688` | `unk1688` | `Unk1688Entry *` (24-byte records) |
| `+0x1694` | `unk1694` | `Unk1694 *` (4-byte records) |
| `+0x16C8` | `unk16C8` | compare cookie for `sub_08073440` |
| `+0x16E0` / `+0x16E4` | `unk16E0` / `unk16E4` | `{ptr, word}` lists |
| `+0x1710` | `unk1710[27]` | `s32` handles (`-1` = empty) |
| `+0x177C` / `+0x1780` | `unk177C` / `unk1780` | `s32` handles |
| `+0x1819` | `unk1819` | last `sub_080603A4` arg |
| `+0x1798` / `+0x179C` | `unk1798` / `unk179C` | copied to/from `*gUnk_03000630` |
| `+0x1800` | `unk1800` | LCG seed / arena word |
| `+0x1808` | `unk1808` | flags (`0x200` / `0x2000`) |
| `+0x1818` | `unk1818` | table-row index |
| `+0x181A` | `unk181A` | last `sub_080603E0` arg |
| `+0x1834` | `unk1834` | flag byte |
| `+0x1861` | `unk1861[0x53]` | signed occupancy bytes |

## C conversion status

| Function | Status |
|----------|--------|
| `sub_080628E4` | **semantic C** — `gMainWorkPtr->unk1800` |
| `sub_080628B4` | **semantic C** — LCG on `unk1800` |
| `sub_080314FC` | **semantic C** — `gBattleWork->unk118` |
| `sub_080433F4` | **semantic C** — `unk1834` / `unk1808` |
| `sub_0802E1EC` | **semantic C** — `sub_08042BE8(unk0874)` |
| `sub_0802BA4C` | **semantic C** — free `*gUnk_03000268`, clear `unk1694` |
| `sub_08044EE8` | **semantic C** — zero `unk1688[idx]` |
| `sub_0803E440` | **semantic C** — count positive `unk1861[]` |
| `sub_0806013C` | **semantic C** — invalidate `unk177C`/`unk1780` |
| `sub_08060220` | **semantic C** — invalidate `unk1710[idx]` |
| `sub_08071FAC` | **semantic C** — `unk16==2` → `1` via `sub_08071F44` |
| `sub_08071FC8` | **semantic C** — clamp `b` to `0x100`, store `unk10` |
| `sub_080603E0` | **semantic C** — `sub_08071FC8` on `unk1710[0..0x18]`, set `unk181A` |
| `sub_080603A4` | **semantic C** — optional `71FC8` on `unk177C`, set `unk1819` |
| `sub_0802D598` | **semantic C** — clear `gUnk_0300026C`, write `0xFFFFC000` into inner +8/+0xC |
| `sub_08043BDC` | **semantic C** — walk `unk16E4` vs `unk16C8` |
| `sub_08060428` family | **semantic C** — thunks to `sub_080601C4` |
| `sub_08072F94` | readable Thumb — agbcc loads `gBtlLookupPtr` before the addend (permuter score 50) |
| `sub_0803DD60` family | readable Thumb — main-work table via `+0x1818` |
| `sub_08034894` | readable Thumb — agbcc prologue / pool ordering |
| `sub_0806FEFC` / `sub_0806FF28` | readable Thumb — object freelist (CSE / extra prologue) |
| `sub_080428C4` / `sub_080475C4` / `sub_080475F4` | readable Thumb — C adds `push {lr}` |
| `sub_0806A6F8` | readable Thumb — large input hub |

13 / 160 battle functions are semantic C (progress.py); more thunks are semantic C but lack battle IWRAM pools. Remainder is readable Thumb (0 opcode `.byte`).

## Tools

```bash
# Rank battle functions by RAM refs + size
python3 tools/decomp/battle_scan.py -n 30

# Verify + integrate hand-written battle C
python3 tools/decomp/match_function.py sub_080628E4 src/matched/sub_080628E4.c
python3 tools/decomp/integrate_c.py sub_080628E4 @src/matched/sub_080628E4.c --note battle/main-work
```
