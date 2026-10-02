# debug_menu

Press **L** in the overworld to open a debug popup in the game's own menu style.

| Key | Action |
| --- | --- |
| Up / Down | move (scrolls, six rows visible) |
| A | toggle the entry, or step a setting forward |
| Left / Right | change a setting (movement speed, BGM) |
| B / L / Start | close |

```
make MOD=debug_menu      # -> beyblade_g_revolution_debug_menu.gba
```

State is kept in RAM only (it resets when the console is reset). Entries that
hold a value restore the original when switched off; entries that give things
take back only what they added.

## Entries

| Entry | What it does | Checked |
| --- | --- | --- |
| Max RPM | Player launch RPM, live spin and spin cap set to 32767 after the retail launch formula (`sub_0803CECC`). 32767 is the largest value the retail signed spin step handles. | wrapper only: values written, retail untouched when off. Not run in a live battle. |
| Max STR | `MainWork.strength` = 99 | yes, value and restore |
| Max EXP | `MainWork.expPoints` = 0x3FFF (the cap `BtlApplyClampedScore` uses) | yes |
| Max Level | `expPoints` = 4000, the first experience of level 16. Max EXP wins if both are on. | yes |
| Max Credits | `MainWork.unk0870` = 99999. This word is the money: the shop (`sub_0802FD80`) subtracts the price from it and script commands 95/98/99 compare and add to it. | yes |
| All BeyBlades | Adds all 83 beyblade templates (inventory group 1) | yes, collection screen |
| All Parts | Adds every ripcord (group 2, ids 1-4), launcher (group 3, ids 1-4) and bit chip (group 7, ids 0-6) | yes, collection screens |
| All Characters | Marks all 55 blader rows as collected, so "Meet bladers" lists them (`row[7] & 1`) | yes |
| All Locations | **n/a**, see below | |
| Max BitBeast EXP | `bitBeastExp` = 0x3FFF on every collected blader row | value and restore, not seen in a battle |
| Inf. BeyBlade Health | Never lose the equipped beyblade after a loss (hook inside `sub_08037F98`, port of the earlier `keepBeybladeOnLoss`) | all branches of the hook |
| Infinite Ripcord / Launcher | The equipped part keeps full health after a battle (wraps both callers of `BattlePartsApplyWear`) | yes, with strength 99 the retail code frees both parts |
| Movement Speed | x1..x4 on the overworld step (`sub_08041E88`) | yes |
| BGM | Left/Right plays a track by name (`sub_0805FED4`); names and numbers are in the shared `include/bgm.h` | track and sound handle change, not heard |
| Character | **n/a**, see below | |

## What else changes

- `ExpBracket` (`sub_08042BE8`) and `ExpBarFill` (`sub_0802E1B4`) are replaced
  by versions that give level 16 and a full bar from 4000 experience.
  Retail returned -1 there and broke the HUD. Identical for 0..3999 (checked
  against the retail ROM for every value).
- `HeapAlloc` is patched to size the heap as `0xFC << 10` instead of
  `0xFE << 10`, freeing the top 4 KB of EWRAM (`0x0203F000`) for `gDebug`.

## Not done

- **All Locations.** There is no "locations" list in the menus. The world map
  walks a node graph (`MapCursorInput`, `gUnk_03000554/558`) and the gates
  are not in the decomp yet: it is not known whether a node is opened by an
  event flag (`gData_03000610`, 256 flags), a script byte, or a node bit.
  Setting every flag would also play every cutscene. Needs a decision on what
  "all locations" should unlock.
- **Character.** The overworld player object starts from template
  `0x083147C8` (`MapLoadObjects` loads its palette `0x083002E0`); `sub_08046324`
  switches it to template `0x08315B88` / palette `0x083006E0` when
  `MainWork+0x1844` is 1. Setting that byte and changing maps did not change the
  sprite, so that is not the switch. A second object (`MainWork+0x448`, enabled
  by `unk182C`) is a follower.
