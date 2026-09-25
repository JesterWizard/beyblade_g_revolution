# fixHighExpRpm

`sub_080302E0` steps a blade by `(rpm << 16) / 0x900` using a signed divide. At 32768 and above the shift is negative, the blade steps backward, and the fight treats it as already stopped. The same overflow can happen inside the launch formula when the experience base at `0x030002A0+8` is itself 32768 or higher, which stores a negative RPM.

With the flag set, a non-positive player-0 RPM is rebuilt with an unsigned multiply from that base, power (`BattleWork+0x1F74`), boost (`+0x1F76`), and `MainWork.strength`. Any non-negative RPM is then stepped with an unsigned divide.

`configs/runtime.c`: `fixHighExpRpm`. `FALSE` calls the retail divider at `0x080740B0`. Byte 10 of `RuntimeConfig` in `include/runtime.h`.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `fixHighExpRpm` |
| `configs/runtime.c` | The value |
| `src_custom/high_exp_rpm.c` | Replacement |
| `src_custom/LynJump.event` | Stub at ROM file offset `$302E0` |
| `Makefile` | `high_exp_rpm.c` is linked only for `make HACKS=1 modern` |

## Functions

- Replaces `sub_080302E0` (`0x080302E0`) with `SpinStep__Replacement`.
- A rebuilt player-0 value is written to `BattleWork+0x13C`, `+0xBB4`, `+0x144`, and `0x030002A0+12`.
- The step still updates the phase word at `BattleWork+0xAE8` and the spin frame through `sub_08070354`. A large step picks a frame with `sub_080628B4`.
- Flag off, or a negative value, uses the retail signed divider at `0x080740B0`.

## Limitations

- The rebuild runs only for player 0, and only when the stored RPM is already 0 or negative. A positive RPM at 32768 or above is not rebuilt; it is only stepped with the unsigned divide.
- The unsigned step applies to both fighters whenever the stored RPM is 0 or positive.
- The rebuilt value has a floor of 1. It includes the retail quarter bonus when power and boost are both above 94.
- The HUD can still show 99999. This flag does not change the five-digit display.
- It does not change how experience is awarded or capped.
