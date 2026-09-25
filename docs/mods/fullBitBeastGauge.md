# fullBitBeastGauge

`sub_08031094` fills a fighter's bit-beast gauge from current spin versus the spin cap. The reading is 0..36. The bar object stores the inverse (`36 - fill`).

With the flag set, player 0's reading is forced to 36 and the bar frame is forced to full, whenever this function is called with a bar object.

`configs/runtime.c`: `fullBitBeastGauge`. `FALSE` is retail. Byte 8 of `RuntimeConfig` in `include/runtime.h`.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `fullBitBeastGauge` |
| `configs/runtime.c` | The value |
| `src_custom/bitbeast_gauge.c` | Replacement |
| `src_custom/LynJump.event` | Stub at ROM file offset `$31094` |
| `Makefile` | `bitbeast_gauge.c` is linked only for `make HACKS=1 modern` |

## Functions

- Replaces `sub_08031094` (`0x08031094`) with `BitBeastGaugeFill__Replacement`.
- Player 0 is `BattleWork+0x478`. The gauge word is that fighter's `+0x2F0`. The bar frame is `Unk705DC.unk18`.
- The retail path still calls `sub_08031124` (`ScaleRatio`) for the opponent and for player 0 when the flag is off.

## Limitations

- Player 0 only. The opponent's gauge is retail.
- This does not change bit-beast experience or launch RPM. It only forces the gauge reading.
- The force happens before the retail "no bit beast" check, so the bar reads full even when the blade has no bit-beast mark.
- If the caller passes a null bar, the replacement returns without writing the gauge.
