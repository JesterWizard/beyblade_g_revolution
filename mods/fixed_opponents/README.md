# Fixed Opponents

## 🧩 Introduction

In retail, a scripted opponent is set up from the player: before the battle, a script opcode copies **your** experience and strength (or a rival's) onto the opponent's blader row, plus a small per-fight bonus, and afterwards the opponent keeps gaining experience from your bouts and from story steps. So the more you level, the stronger they launch. This mod removes all of that. Each blader gets the experience and strength set in `opponents.json` (by default the ones it starts a new game with), and nothing raises them, so you can out-level your opponents.

An opponent's launch RPM is `(row experience + blade bit beast experience)` and the row's strength, times their random meters (see [`docs/mechanics.md`](../../docs/mechanics.md)). With those fixed, every opponent has the same RPM range every time, for example row 7 launches from a base of 400 experience / strength 3 and the final rivals from 2000 to 2700.

## 🛠️ How To Use

```
make MOD=fixed_opponents     # only this mod
make                         # all default mods, this one included
```

It is enabled by `MOD_FIXED_OPPONENTS` in [`mods/mods.h`](../mods.h); set it to 0 to get the retail scaling back. Your own experience, strength, and bit beast growth are not touched.

### Setting each opponent

[`opponents.json`](opponents.json) holds one line per blader row (55). Edit the numbers and run `make`:

```json
{"row": 12, "name": "Ray", "exp": 1300, "strength": 8}
{"row": 29, "name": "Rick", "exp": 2700, "strength": 12, "beast_exp": 400}
```

| Field | Range | Meaning |
|-------|-------|---------|
| `row` | 0..54 | The blader row (the game's blader order) |
| `exp` | 0..16383 | Character experience. The bigger lever on launch RPM |
| `strength` | 0..127 | Added as `strength * (power + boost)`, not scaled by experience |
| `beast_exp` | 0..16383 | Optional. The blade's bit beast experience, added to `exp` for the launch. Left out = the saved value is not touched |
| `name` | text | Only a label for you |

A row or a field that is left out keeps the ROM's start value. The file is checked at build time (bad rows, duplicates and out of range numbers stop the build with a message).

To see what the numbers mean in game, `python3 mods/fixed_opponents/tools/gen_opponents.py mods/fixed_opponents --list` prints every opponent with the launch RPM range their numbers give (power is a random 80..99 and boost 75..99, so it is a range; the formula is in [`docs/mechanics.md`](../../docs/mechanics.md)):

```
row  name        exp  str  beast   launch RPM
  7  Skull       400    3      -   1085 - 1732
 29  Rick       2700   12      -   6045 - 9652
```

`--init` rewrites the file with the ROM's start values. The names come from the game's name table indexed by row, so they are a label only (row 40 shows a repeated name).

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Stop the copy from the player** | `call 0x0802CBF0` and `call 0x0805B2BA` in [`hooks.txt`](hooks.txt) | Both script opcodes call `sub_08042F4C(exp, strength, row, bonus)`. `FixedOpponentRow` in [`fixed_opponents.c`](src/fixed_opponents.c) ignores the numbers and writes the row's values from `opponents.json` (built into `gOpponentRows` by [`gen_opponents.py`](tools/gen_opponents.py)). The ROM's own start values are at `0x080909C4` (8 bytes per row: `s16` experience, strength at +3) |
| **No story growth** | `call 0x080323A8` | The function at `0x08042F08` adds 10 experience to every blader row at a story step; replaced by an empty function |
| **No growth from bouts** | `call 0x08037B1A` and `call 0x08037B4C` | `FixedOpponentScore` wraps `BtlApplyClampedScore` (`sub_0803715C`) and puts back the opponents' row experience (`unk24->unk00`) and blade bit beast experience (`unk28->unk26`) afterwards. The player's side still grows |

## 🐛 Limitations & Bugs

- Checked in the emulator by calling the functions on a new game: a row set to 9999 experience / 77 strength is reset to its start values (400 / 3), and with `opponents.json` set to 5000 / 50 / beast 100 for row 7 the row got exactly those, and the score wrapper leaves a row's experience at 400 and its bit beast experience at 0 where the retail function raises them to 420 and 5. Not played through a real tournament.
- A row only gets its values when a script opcode sets up a fight with it. A save made with the retail game, where rows already grew or were copied from the player, keeps those values until that blader's next scripted fight. Bit beast experience is only written when `beast_exp` is set; otherwise it is just stopped from growing.
- The per-fight `bonus` (for example -2 to +3 in the tournament table) no longer applies, so the order of strength follows the start values only.
- The debug menu's "Max BitBeast EXP" writes the blader rows too, so with it on the opponents are strong again.
