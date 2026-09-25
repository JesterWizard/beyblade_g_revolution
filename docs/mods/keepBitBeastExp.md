# keepBitBeastExp

Saving calls `sub_08044E54`, which clears the whole profile and then unpacks it. The unpacker copies the profile's blade table onto live RAM and never copies that table back, so bit-beast experience is written to EEPROM as zero.

With the flag set, the live blade table is snapshotted first, the retail clear and unpack still run, and the snapshot is copied back onto both live RAM and the profile. The profile checksum is then recomputed.

`configs/runtime.c`: `keepBitBeastExp`. `FALSE` is the retail wipe. Byte 9 of `RuntimeConfig` in `include/runtime.h`.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `keepBitBeastExp` |
| `configs/runtime.c` | The value |
| `src_custom/save_bitbeast.c` | Replacement |
| `src_custom/LynJump.event` | Stub at ROM file offset `$44E54` |
| `Makefile` | `save_bitbeast.c` is linked only for `make HACKS=1 modern` |

## Functions

- Replaces `sub_08044E54` (`0x08044E54`) with `SavePrepare__Replacement`.
- The save commit `sub_08044DAC` calls it at `0x08044DDC`.
- Live rows come from `sub_08042E78(0)`. The profile copy sits at record `+0x134C`. The record is `MainWork.unk168C + slot * 0x1F60`.
- `sub_08045198` is the unpacker. `sub_08044D8C` is the checksum, stored back into word 0 of the record.

## Limitations

- Only the blade table is preserved (55 rows, 48 bytes each, `0xA50` bytes). Other profile fields still go through the retail clear and unpack.
- The snapshot uses EWRAM at `0x02030000`. That pool must stay free for the duration of the save.
- If `sub_08042E78(0)` returns null, the replacement falls through to the retail wipe.
- This does not raise the 16383 cap. That is `uncapBitBeastExp`.
