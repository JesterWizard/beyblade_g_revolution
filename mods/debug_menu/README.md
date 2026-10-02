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

A debug popup in the game's own menu style, opened from the overworld. It gives test shortcuts (max stats, every beyblade and part, every location, character swaps, BGM player) without editing a save, an **Abilities** section with five special battle abilities for the player, and a **Weather** entry (rain, snow, wind, heat) that is drawn in the overworld and in battle and changes how a battle plays.

The menu's state is stored in the save, in the 8-byte EEPROM blocks after the save slot (blocks `0x3EF..0x3FB`, up to 100 bytes; the slot itself has no room). It is written right after the slot's data blocks and read when the slot loads, so toggled entries stay on after a reset. The record has its own tag and sum (retail's checksum does not cover it); a missing or damaged record loads as every entry off. Besides the values it keeps the originals the value entries restore and what the collection entries added, so switching an entry off after a reload still takes back exactly what it gave. The abilities' on/off bits are a small second part (tag, bits, sum) in the last block of the record, and the weather a third (tag, value, sum) behind it, so a record written before either existed still loads, with them off. Not saved: each blader's original bit beast EXP (110 bytes), so Max BitBeast EXP does not restore after a reload.

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
| Left / Right | change a setting (movement speed, BGM, character, weather) |
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
| Character | Left/Right steps through every sprite and palette pair the NPC table uses (94; Tyson = OFF). Sets the overworld sprite with the palette the game itself uses for it. 53 get their blader's portrait, name, STR / EXP / LVL and dialogue portrait; 31 more get the dialogue portrait of a non-blader NPC (face only, Tyson's numbers stay); the last 10 (generic kids) have no portrait and show "NPC <id>" with Tyson's. Kept across map changes. | built, not run in game |
| **Abilities** (heading) | The section for the five entries below. The cursor skips the heading. Every ability works on the player only (fighter index 0); the opponent plays by the retail rules. Each wraps one `bl` in the battle code (see Code Locations). | menu |
| Siphon | 10% of the spin a clash takes from the opponent is added to the player's. A hit is only a few spin points, so the hundredths are carried over to the next hit (a 9 point hit pays 0, the next 1, ...). Capped at 32767. | yes, in a live duel: a 1000 point hit pays 100 |
| Gunner | The bit beast gauge fills 50% faster: every time the blades touch the gauge gets `0x30` instead of `0x20`, up to its capacity. | yes, `0x30` per touch |
| Steel Wall | Half of the spin that attacking and jumping/dodging cost is given back, taken over the whole input handler `sub_08034BE0` (attack release: endurance/2, endurance or 1.5 x endurance; dodge and jump: endurance/2). Odd costs round in the player's favour. Clash damage is not reduced. | yes, an attack that cost 5 costs 2 |
| Turbine | Every frame the player is 140+ units from the arena centre (the wall is at about 199) and moving across the line from the centre faster than 1 unit a frame builds one point of charge, up to 300 (5 seconds of edge travel). At full charge the d-pad steers 100% stronger (the blade's top speed doubles) and an attack hits 50% harder; both scale with the charge. The charge is lost when the blades touch (a clash, or the bodies colliding) and when a battle starts. | yes, a bot that circles the edge reaches full charge and double speed; a charged attack hits 100 -> 150 and the charge resets |
| Rocket | The recovery wait after an attack (the wait before the next one is allowed, 75, 90 or 120 frames) counts down twice as fast. The short clash scene before it is not changed. | yes, 143 -> 105 frames between two attacks |
| **Weather** (heading) | The section for the entry below. | menu |
| Condition | Off / Rain / Snow / Wind / Heat (Left/Right). Every one draws OBJ particles on the overworld (towns and the world map; not while the menu is open) and in battle, and also changes a battle. It affects both blades, not just the player's. **Rain** = reduced grip: the arena's drag is cut to 60% (blades slide further after the d-pad is released) and the d-pad's push to 60%, so the top speed stays about the same and turns get wide. **Snow** = increased friction: drag x1.75, so everything slows down sooner and the top speed falls to about 60%. **Wind**: a sideways push of up to 10 (full steering is 32) on both blades, in screen terms (rotated into the arena with the same camera turn the d-pad uses), swinging from one side to the other over about 17 seconds with gusts on top; the streaks on screen run the way it blows and thin out when it is calm. **Heat**: each blade loses 1% of its spin (at least 1) every 40 frames, about 1.5% a second, on top of the retail drain. | particles in town and in a live duel (screenshots), drag and top speed against Off in the duel, heat's spin loss; wind's direction is derived from the d-pad's transform, not watched |

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
| **Character** | `HoldCharacter`, `DebugObjPalLoad`, `DebugPortraitOp` in [`cheats.c`](src/cheats.c) | Sprite swap; `pointer 0x08099784` wraps script opcode 29 for the dialogue portrait |
| **Look table** | [`character_looks.c`](src/character_looks.c), generated by [`gen_looks.py`](tools/gen_looks.py) | Every (template, palette) pair of the scene NPC table |
| **Movement speed** | `DebugMoveStep` in [`cheats.c`](src/cheats.c) | `call 0x080470C2` |
| **Infinite parts** | `DebugPartsApplyWear` in [`cheats.c`](src/cheats.c) | `call 0x0803B826` and `0x0803BA32` |
| **Max RPM / full gauge** | `DebugLaunch` in [`cheats.c`](src/cheats.c) | `call 0x0803C230` |
| **Abilities** | `AbilityHandler`, `TurbineSteer`, `TurbinePower`, `AbilityClash`, `AbilityContact`, `AbilityUpdate` in [`abilities.c`](src/abilities.c), types in [`battle_types.h`](include/battle_types.h) | `call 0x08031D82` / `0x08031D90` (input handler `sub_08034BE0`: Steel Wall, Turbine count), `0x08034C10` / `0x08034D08` (steering `sub_08030638`: Turbine speed), `0x08032B24` (clash `sub_0802FFAC`: Siphon, Turbine reset), `0x0802FFC0` / `0x0802FFC8` (action power `sub_080300D4`: Turbine attack), `0x08031F90` (contact `sub_08032A88`: Gunner), `0x0803021A` / `0x08030224` (fighter update `sub_080348E8`: Rocket) |
| **Weather** | `Frame`, `Draw`, `StepParticles` in [`weather.c`](src/weather.c); art in [`weather_gfx.c`](src/weather_gfx.c), generated by [`gen_weather_gfx.py`](tools/gen_weather_gfx.py) | Called from `DebugFieldTick` (overworld) and `AbilityHandler` (battle, once per frame). OBJ tiles `0x370..0x378`, palette slot 14, OAM 98..125 |
| **Weather in battle** | `WeatherMotion`, `WeatherSteer`, `WeatherDrain` in [`weather.c`](src/weather.c) | `call 0x08034926` (motion step `sub_08035984` inside `sub_080348E8`: rain, snow, wind); rain's steering goes through `TurbineSteer`, heat through `AbilityUpdate` |
| **Section heading** | `DebugIsHeading`, `MoveCursor` in [`debug_menu.c`](src/debug_menu.c) | a heading row is drawn centred and skipped by the cursor |
| **Keep blade** | `KeepBladeOnLoss__Hook` in [`keep_blade.s`](src/keep_blade.s) | Mid-function hook at `0x080380E0` |
| **BGM names** | `BgmName` in [`bgm.c`](src/bgm.c) | Track names for the BGM entry |
| **HUD fix** | `ExpBracketFixed`, `ExpBarFillFixed` in [`cheats.c`](src/cheats.c) | Replace `sub_08042BE8` and `sub_0802E1B4` |
| **State / heap** | `DebugStateInit` in [`debug_menu.c`](src/debug_menu.c), [`ram.s`](src/ram.s), `patch 0x0806A3DE` / `0x0806A622` | `gDebug` at `0x0203F000` and the heap shrink |

---

## 📝 TODO

- Run Max RPM, infinite parts and Max BitBeast EXP in a real battle
- The abilities were checked in an emulator save state of a live duel, not played through; Turbine's numbers (`TURBINE_*` in `abilities.c`) are a first guess to tune by feel
- Name more NPC looks (`MAIN` in `gen_looks.py`)

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- **Weather.** The particles are plain OBJ sprites written into OAM during the frame, the way `thought_bubbles` does it (the engine hides the entries it does not use at the start of each frame, so nothing is left behind when the weather is switched off). That works in mGBA; it has not been tried on hardware. They also appear indoors, and the overworld ones pause while the menu is open. The tiles `0x370..0x378` are free in the town and duel screens that were checked; a battle effect that loads a lot of OBJ art could overlap them (they are reloaded if overwritten). Heat can drain a blade to 0 spin; the duel did not end at once when that happened in the emulator (the HUD counts down first), and no duel was followed through to its end that way.

- **Character.** The list is every distinct (template, palette) person sprite of the scene NPC table (`0x0807BE04`, palette `gData_080775CC[id]` at `0x080775CC`). The ROM does not link an NPC sprite to a blader portrait, so the pairing (`MAIN` in the generator, blader portrait -> NPC id) was matched by eye, sprite sheet against the 55 blader portraits and the 49 extra dialogue portraits (`EXTRA` in the generator); the shirtless-kid portraits (14 to 18) and 27, 47 to 50 are the least certain. The portrait uses OBJ palette slot 13, not slot 2, because the HUD digits and bars use slot 2's palette. The dialogue variant shown while event flag 77 is set is left alone.
- **All Locations.** It opens paths and map art. The low nibble of a flag byte (what A can enter) keeps its start value, so the six junction nodes (1, 2, 3, 7, 10, 15) stay pass-through, as in the retail game.

---
