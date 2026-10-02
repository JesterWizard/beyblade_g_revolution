# Debug Menu

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Entries](#entries)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

A debug popup in the game's own menu style, opened from the overworld. It gives test shortcuts (max stats, every beyblade and part, every location, character and sprite swaps, BGM player) without editing a save.

The menu's state is stored in the save, in the 8-byte EEPROM blocks after the save slot (blocks `0x3EF..0x3FB`, up to 100 bytes; the slot itself has no room). It is written right after the slot's data blocks and read when the slot loads, so toggled entries stay on after a reset. The record has its own tag and sum (retail's checksum does not cover it); a missing or damaged record loads as every entry off. Besides the values it keeps the originals the value entries restore and what the collection entries added, so switching an entry off after a reload still takes back exactly what it gave. Not saved: each blader's original bit beast EXP (110 bytes), so Max BitBeast EXP does not restore after a reload.

Besides the menu it changes two retail routines:

- `ExpBracket` (`sub_08042BE8`) and `ExpBarFill` (`sub_0802E1B4`) are replaced by versions that give level 16 and a full bar from 4000 experience. Retail returned -1 there and broke the HUD. Identical for 0..3999 (checked against the retail ROM for every value).
- `HeapAlloc` is patched to size the heap as `0x80 << 10` (128 KB) instead of `0xFE << 10`, freeing `0x02020800`–`0x02040000` of EWRAM; `gDebug` sits in it at `0x0203F000`.

---

## 🛠️ How To Use

```
make                    # default mods, with thought_bubbles
make MOD=debug_menu     # only this mod
```

Press **Select** in the overworld.

| Key | Action |
| --- | --- |
| Up / Down | move (scrolls, six rows visible) |
| A | toggle the entry, or step a setting forward |
| Left / Right | change a setting (movement speed, BGM, character, sprite, palette) |
| B / Select / Start | close |

---

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
| All Locations | Opens every path and spot on the world map: each node's saved flag byte (`gUnk_03000554`+8, 16 bytes) gets its start state plus a bit for every path the node table (`0x08094B68`) links, and the map art's path flags (event flags 35, 36, 48, 52, 53, 57, 58, tested by `sub_08043980`) read as set without being set, so no cutscene plays. Only the bits it added are cleared when switched off. | node bytes and the art test checked in the emulator, walking a path that was closed (node 2 up to node 15). Not seen on a real map screen. |
| Max BitBeast EXP | `bitBeastExp` = 0x3FFF on every collected blader row | value and restore, not seen in a battle |
| Start Full Gauge | The player's bit beast gauge starts a battle full (three bars): `BattleWork+0xBBC` = its capacity `+0xBC4` right after the launch formula (`sub_0803CECC`). It then fills and empties as normal. Pairs with `mods/bitbeast_bars`. | yes, gauge 36 at the start of a battle, the summon uses it |
| Inf. BeyBlade Health | Never lose the equipped beyblade after a loss (hook inside `sub_08037F98`, port of the earlier `keepBeybladeOnLoss`) | all branches of the hook |
| Infinite Ripcord / Launcher | The equipped part keeps full health after a battle (wraps both callers of `BattlePartsApplyWear`) | yes, with strength 99 the retail code frees both parts |
| Movement Speed | x1..x4 on the overworld step (`sub_08041E88`) | yes |
| BGM | Left/Right plays a track by name (`sub_0805FED4`); names and numbers are in the shared `include/bgm.h` | track and sound handle change, not heard |
| Character | Left/Right steps through every sprite and palette pair the NPC table uses (94): Max, Daichi, Kenny, Kai, Grandpa, Bonz and Jin of the Gale by name, then "NPC <id>" for the rest (Tyson = OFF). Sets the overworld sprite with the palette the game itself uses for it. Named ones also get their HUD portrait, STR / EXP / LVL and dialogue portrait; "NPC" entries keep Tyson's. Kept across map changes. | yes: all 94 rendered, walk, menu, HUD, dialogue, map change, restore |
| Sprite | Left/Right picks any of the 70 person walking sprites in the ROM (OFF = follow Character). | all 70 rendered |
| Palette | Left/Right picks any of the 120 OBJ palettes the game uses for them (OFF = follow Character). Together with Sprite this reaches every look, including characters no NPC row pairs (the ROM does not say which palette a cutscene gives them). | menu, sprite change |

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Menu loop** | `DebugFieldTick`, `OpenMenu`, `MenuLoop` in [`debug_menu.c`](src/debug_menu.c) | Opens on Select and runs the popup; hooked at `call 0x080470FC` |
| **Menu drawing** | `DrawAll`, `DrawRow`, `ValueText` in [`debug_menu.c`](src/debug_menu.c) | Frame, rows, highlight and value text |
| **Input** | `OnUp`, `OnDown`, `OnA`, `OnLeft`, `OnRight`, `OnB` in [`debug_menu.c`](src/debug_menu.c) | One handler per key; `Step` changes a setting |
| **Cheat tick** | `CheatsTick`, `CheatsOnToggle`, `CheatsOnChange` in [`cheats.c`](src/cheats.c) | Holds the values written each frame and gives/takes items |
| **Max stats / money** | `HoldStrength`, `HoldExp`, `HoldCredits`, `HoldBitBeastExp` in [`cheats.c`](src/cheats.c) | Value entries |
| **Collections** | `GiveBeyblades`, `GiveParts`, `HoldCharacters` in [`cheats.c`](src/cheats.c) | All BeyBlades / Parts / Characters |
| **World map** | `HoldLocations`, `DebugMapFlag` in [`cheats.c`](src/cheats.c) | Opens paths; `DebugMapFlag` at `call 0x080439B6` |
| **Character / sprite / palette** | `HoldCharacter`, `DebugObjPalLoad`, `DebugPortraitOp` in [`cheats.c`](src/cheats.c) | Sprite swap; `pointer 0x08099784` wraps script opcode 29 for the dialogue portrait |
| **Look table** | [`character_looks.c`](src/character_looks.c), generated by [`gen_looks.py`](tools/gen_looks.py) | Every (template, palette) pair of the scene NPC table |
| **Movement speed** | `DebugMoveStep` in [`cheats.c`](src/cheats.c) | `call 0x080470C2` |
| **Infinite parts** | `DebugPartsApplyWear` in [`cheats.c`](src/cheats.c) | `call 0x0803B826` and `0x0803BA32` |
| **Max RPM / full gauge** | `DebugLaunch` in [`cheats.c`](src/cheats.c) | `call 0x0803C230` |
| **Keep blade** | `KeepBladeOnLoss__Hook` in [`keep_blade.s`](src/keep_blade.s) | Mid-function hook at `0x080380E0` |
| **BGM names** | `BgmName` in [`bgm.c`](src/bgm.c) | Track names for the BGM entry |
| **HUD fix** | `ExpBracketFixed`, `ExpBarFillFixed` in [`cheats.c`](src/cheats.c) | Replace `sub_08042BE8` and `sub_0802E1B4` |
| **State / heap** | `DebugStateInit` in [`debug_menu.c`](src/debug_menu.c), [`ram.s`](src/ram.s), `patch 0x0806A3DE` / `0x0806A622` | `gDebug` at `0x0203F000` and the heap shrink |

---

## 📝 TODO

- Run Max RPM, infinite parts and Max BitBeast EXP in a real battle
- Name more NPC looks (`MAIN` in `gen_looks.py`)

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- **Character.** The list is every distinct (template, palette) person sprite of the scene NPC table (`0x0807BE04`, palette `gData_080775CC[id]` at `0x080775CC`). The ROM does not say who an NPC is, so only a few are named (picked by eye, `MAIN` in the generator). Kai and Kenny have no human portrait, so their HUD / dialogue portrait is their bit beast's. The portrait uses OBJ palette slot 13, not slot 2, because the HUD digits and bars use slot 2's palette. The dialogue variant shown while event flag 77 is set is left alone.
- **All Locations.** It opens paths and map art. The low nibble of a flag byte (what A can enter) keeps its start value, so the six junction nodes (1, 2, 3, 7, 10, 15) stay pass-through, as in the retail game.

---
