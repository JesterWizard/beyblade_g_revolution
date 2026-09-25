# keepBeybladeOnLoss

`sub_08037F98` compares `BattleWork+0x138` with `+0x139`. The higher byte wins and takes the opponent's blade. The lower byte loses the equipped beyblade, unless the battle mode is 7, 8, 9, 10, or 11, or it is the last blade of that type.

With the flag set, a loss takes the same spare path retail uses for those exemptions. The equipped beyblade stays.

`configs/runtime.c`: `keepBeybladeOnLoss`. `FALSE` resumes the retail loss check. Byte 11 of `RuntimeConfig` in `include/runtime.h`. The assembly loads that byte by offset.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `keepBeybladeOnLoss` |
| `configs/runtime.c` | The value |
| `src_custom/keep_blade.s` | `KeepBladeOnLoss__Replacement` |
| `src_custom/LynJump.event` | Stub at ROM file offset `$380E0` |
| `Makefile` | `keep_blade.s` is linked only for `make HACKS=1 modern` |

## Functions

- Hooks inside `sub_08037F98` (`0x08037F98`) at `0x080380E0`, which is the win/loss compare. The stub is 16 bytes. Flag off resumes at `0x080380F0` with the mode word from `0x030002A0+0x2C` in `r0`.
- A loss with the flag on branches to `0x08038144`.
- A draw branches to `0x0803814C`.
- The retail loss continuation, including modes 7, 9, and 10 and the last-blade check, is `0x080380F0`.

## Limitations

- Winning still takes the opponent's blade. This only skips the loss removal.
- An earlier path in the same function removes a blade when the collection record's byte at `+0x24` is 100. That path is not hooked. Stock ROM templates store 0 there.
- The literal pool at `0x0803813C` is left in place. The stub must stay 16 bytes so it is not overwritten.
