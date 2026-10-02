# Show Math

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

The workshop's blade screen shows Attack, Defense and Endurance only as stars, and nothing about launch RPM. This mod prints the numbers behind them next to the stars:

| Row | Shows | Meaning |
| --- | --- | --- |
| ATT | `8/16/24` | attack power of a low / medium / high charge attack (sum x 1 / x 2 / x 3) |
| DEF | `5/10/15` | defending power at the same three charges |
| END | `RPM 204` | launch RPM of a perfect ripcord pull: power meter 100, boost 0 |

The formulas are the retail ones (see [docs/mechanics.md](../../docs/mechanics.md)):

```
attack  = ring + disk + base (byte 0 of the part rows) + exp / 100
defense = ring + disk + base (byte 1)                  + exp / 100
quot    = (exp << 16) / 25600
rpm     = (quot * (100 << 8)) >> 16 + strength * 100       (boost 0, so no boost term and no 95+ bonus)
```

`exp` is the launch base the battle setup uses for the player: the character's experience (`MainWork.expPoints`, the EXP on the HUD) plus the blade's bit beast experience (the "Exp" on the panel). `strength` is the character's strength (STR on the HUD).

---

## 🛠️ How To Use

```
make                     # default mods, with show_math
make MOD=show_math       # only this mod
```

Open the workshop (R in the overworld, "Go to workshop") and pick a blade.

---

## 🗂️ Code Locations

| Feature | Location | Description |
| --- | --- | --- |
| **Hook** | [`hooks.txt`](hooks.txt) | `call 0x0805035C`: the `bl sub_080507B8` in `DetailPanelDraw` (`sub_0804FFCC`) that commits the panel's text rows |
| **Numbers** | `DrawMath` in [`math.c`](src/math.c) | Reads the part rows (`gData_0807BDB8` disk, `gData_0807BB80` base, `gData_0807B6F0` ring) like `BeybladeGetType` does |
| **Selection bar** | `ShowMathBar` in [`math.c`](src/math.c) | While a part is being picked, the grey bar of the selected part starts after the numbers instead of running across them (hooks on the three places that commit the row palettes) |
| **Drawing** | `Draw`, `DrawTriple` in [`math.c`](src/math.c) | The game's own `TextSetCursor` + `TextDrawAlign` into the panel's active text window, same font as the "Exp" digits |

---

## 🐛 Limitations & Bugs

- Checked in mGBA on the workshop screen (the numbers match the formulas above and the part tables). The RPM was not compared against a real launch in a battle: with the author's save (character exp 146, blade exp 10, STR 2) it shows 355, and a launch measured by the user was 354 (likely before the last experience gain).
- Attack and defense are the raw power before a clash: opponent defense, both sides attacking (both halved) and the other clash rules in `docs/mechanics.md` still apply.
- The real launch is the power meter plus the boost meter; the mod assumes a perfect first meter and no boost, as asked. A perfect boost as well adds the boost term and, above 94 on both, a quarter on top.
- Only the workshop blade panel is changed; the collection's detail screen is a different screen and shows nothing new.
