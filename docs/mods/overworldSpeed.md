# overworldSpeed

`sub_08041E88` stores its speed argument at `MainWork+0x17B0`, then switches on the direction. The overworld frame passes `0x100` while walking and `0x200` while B is held. The cardinal movers copy that word, or its negation, into `MainWork+0x3AC` (X) and `+0x3B0` (Y). `0x100` per frame is one pixel.

This byte multiplies that argument before it is stored. `1` is retail speed. `2` is twice as fast, and it scales both the walk and the B-button run. `0` stores a zero step, so the character stands still while a direction is held.

`configs/runtime.c`: `overworldSpeed`. Byte 14 of `RuntimeConfig` in `include/runtime.h`. The assembly loads that byte by offset.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `overworldSpeed` |
| `configs/runtime.c` | The value |
| `src_custom/overworld_speed.s` | `OverworldSpeed__Replacement` |
| `src_custom/LynJump.event` | Stub at ROM file offset `$41E88` |
| `Makefile` | `overworld_speed.s` is linked only for `make HACKS=1 modern` |

## Functions

- Hooks the start of `sub_08041E88` (`0x08041E88`). The first 16 bytes are the stub. Retail continues at `0x08041E98` with the direction still in `r2` and the `cmp r2, #16` flags set.
- The only caller is `sub_08046E7C`, which picks `0x100` or `0x200` at `0x08046F52` / `0x08046F66` and calls this at `0x080470C2`.
- Direction 0 still runs `sub_08041F88`, which zeros both velocity words. Directions 1, 2, 4, and 8 run `sub_08041FDC`, `sub_08042080`, `sub_08042120`, and `sub_080421C0`.

## Limitations

- The multiplier is a byte, so the largest value is 255. `0x200 * 255` still fits in the 32-bit multiply.
- Holding B still doubles the base before the multiply. The two speeds are not independent.
- Menu cursor movement is a different function and is not scaled.
- `gUnk_03000538` values such as `0x80` and `0x100` are animation state, not this step.
