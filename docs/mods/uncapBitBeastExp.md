# uncapBitBeastExp

Retail `sub_0803EAC0` adds or subtracts 16 from a blade's bit-beast experience, then masks the result with `0x3FFF` (0..16383). The next +16 past 16383 wraps to 0.

With the flag set, that mask is skipped. The result is clamped to 0..32767, which is the range of the signed halfword `Unk42E78.bitBeastExp`.

`configs/runtime.c`: `uncapBitBeastExp`. `FALSE` is retail. Byte 0 of `RuntimeConfig` in `include/runtime.h`.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `uncapBitBeastExp` |
| `configs/runtime.c` | The value |
| `src_custom/bitbeast_exp.c` | Replacement |
| `src_custom/LynJump.event` | Stub at ROM file offset `$3EAC0` |
| `Makefile` | `bitbeast_exp.c` is linked only for `make HACKS=1 modern` |

## Functions

- Replaces `sub_0803EAC0` (`0x0803EAC0`) with `BitBeastAdjustExp__Replacement`.
- Reads the blade index from the word at `0x03000468` and the row through `sub_08042E78`.

## Limitations

- Only this ±16 adjuster is changed. Post-battle awards in `BtlApplyClampedScore` (`sub_0803715C`) still stop the bit-beast halfword at 16383.
- 32767 is the type limit. The field is a signed halfword.
- Saving is a separate option (`keepBitBeastExp`). This flag does not stop the save wipe.
- Level display still uses `ExpBracket` (`sub_08042BE8`). Experience at 4000 or above makes that function return -1, so the HUD level is wrong even though the experience value itself is stored.
