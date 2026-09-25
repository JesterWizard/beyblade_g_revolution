# setRPMTo

After the retail launch formula in `sub_0803CECC`, player 0's launch RPM and spin cap are overwritten with this value.

`0` leaves the retail formula (the usual cap is 9216). `1`..`99999` is written as the starting RPM. Anything above `99999` is clamped to `99999`.

`configs/runtime.c`: `setRPMTo`. Word at offset 4 of `RuntimeConfig` in `include/runtime.h`. The three bytes in front of it (`_padSetRpm`) exist so the word stays 4-aligned. Do not reorder the struct; the assembly loads this offset directly.

## Files

| File | Role |
| --- | --- |
| `include/runtime.h` | Field `setRPMTo` |
| `configs/runtime.c` | The value |
| `src_custom/start_rpm.s` | `StartRpm__Replacement` and `StartRpm_Finish` |
| `src_custom/LynJump.event` | Stub at ROM file offset `$3CECC` |
| `Makefile` | `start_rpm.s` is linked only for `make HACKS=1 modern` |

## Functions

- Hooks the start of `sub_0803CECC` (`0x0803CECC`). The first 16 bytes are the stub. Retail continues at `0x0803CEDC`.
- When the value is not 0, `StartRpm_Finish` runs as that function returns and writes the same word to:
  - `BattleWork+0xBB4` (computed RPM)
  - `BattleWork+0xBBC` (live spin)
  - `BattleWork+0xBC4` (spin cap)
  - `BattleWork+0x13C` and `+0x144`
  - `0x030002A0+12` (player 0's `unk0C`)

## Limitations

- Player 0 only. The opponent's launch is unchanged.
- The spin cap is set to the same number, so live spin cannot climb past it during the fight.
- A value of 32768 or more still breaks the per-frame spin step unless `fixHighExpRpm` is also on. The step shifts the RPM left by 16 as a signed number.
- The on-screen counter is five digits. `99999` is the top of that display.
