# Battle subsystem (decomp notes)

_Agent-maintained. RAM names live in `asm/ram_map_iwram.s` / `include/battle.h`._

## IWRAM map (provisional)

| Symbol | Address | Role |
|--------|---------|------|
| `gMainWorkPtr` | `0x03000198` | Pointer to root main-work arena |
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
| `sub_080628E4` | Write main-work slot @ `+0x1800` (C in `src/matched/`) |

## C conversion status

| Function | Status |
|----------|--------|
| `sub_080628E4` | **C** — `src/matched/sub_080628E4.c` |
| `sub_080314FC` | **C** — `src/matched/sub_080314FC.c` |
| `sub_08072F94` | asm — literal-pool load order (agbcc mismatch) |
| `sub_08034894` | asm — agbcc prologue / pool ordering |
| `sub_0806FEFC` / `sub_0806FF28` | asm — object freelist + pools |
| `sub_0806A6F8` | asm — large |

## Tools

```bash
# Rank battle functions by RAM refs + size
python3 scripts/decomp/battle_scan.py -n 30

# Verify + integrate hand-written battle C
python3 scripts/decomp/match_function.py sub_080628E4 src/matched/sub_080628E4.c
python3 scripts/decomp/integrate_c.py sub_080628E4 @src/matched/sub_080628E4.c --note battle/main-work
```
