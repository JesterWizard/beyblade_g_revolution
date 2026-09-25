# infiniteRipcordHealth

Equipped parts live in `Unk1694`. Type 2 is a ripcord. `unk02` is its health and starts at 100. `sub_0803D51C` subtracts the part id plus `MainWork.strength` from that byte on each hit. At 0 or below the part is removed, `0x030002A0+0x0C` is forced to 0, and the battle treats the blade as empty.

With the flag set, the ripcord block of that function is skipped, so the health byte is not reduced.

`configs/runtime.c`: `infiniteRipcordHealth`. `FALSE` is retail wear. Byte 12 of `RuntimeConfig` in `include/runtime.h`.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `infiniteRipcordHealth` |
| `configs/runtime.c` | The value |
| `src_custom/part_health.c` | Shared replacement for both part-health flags |
| `src_custom/LynJump.event` | Stub at ROM file offset `$3D51C` |
| `Makefile` | `part_health.c` is linked only for `make HACKS=1 modern` |

## Functions

- Replaces `sub_0803D51C` (`0x0803D51C`) with `PartHealth__Replacement`.
- Retail wear looks the part up with `sub_0802C314`, removes it with `sub_0802C55C`, and may set `BattleWork.unk1F73` from `sub_0802C5DC`. The broken flag for a ripcord is `BattleWork.unk131`.
- The launcher is the same function, gated by `infiniteLauncherHealth`.

## Limitations

- Does not heal a ripcord that is already worn or already broken. It only stops further subtraction.
- The launcher still wears unless `infiniteLauncherHealth` is set. Beyblades (type 1) are not covered.
- `MainWork.unk1808 & 0x10000` still returns immediately, matching retail, and wears nothing.
- The damage bar in `sub_08039BD4` still draws from the stored health byte. A new ripcord at 100 shows an empty damage bar, which is retail.
