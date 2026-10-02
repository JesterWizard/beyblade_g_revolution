# BitBeast Bars

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

The bit beast gauge holds up to three bars (36 units, 12 to a bar). Retail summons the bit beast with L+R and always spends everything: the number of full bars (`gauge / 12`) picks the 1, 2 or 3 bar animation and the gauge goes to zero.

This mod stops the battle when you press L+R with **two or more full bars** (the scene stays on screen, faded like the pause screen) and shows a big copy of the HUD's gauge wheel in the middle of the screen: cut into three slices (spokes down, up left, up right), one per bar: lower left blue / teal, top green / yellow, lower right red / orange. Above it is the **estimated damage** of the summon with the chosen bars, e.g. `598 RPM`, in red when it would take all of the opponent's RPM. You choose how many of the bars to spend; the summon then plays with that many, and the bars you did not spend stay in the gauge.

With fewer than two full bars nothing changes, the summon runs as in retail.

---

## 🛠️ How To Use

```
make                       # default mods, with bitbeast_bars
make MOD=bitbeast_bars     # only this mod
```

In a battle, press **L+R** with two or more full bars.

| Key | Action |
| --- | --- |
| Left / Right | spend one bar less / more (1 to the number of full bars, at most 3) |
| A | summon with the chosen number of bars |
| B | cancel, no summon, the gauge is untouched |

The popup opens on the full number of bars, which is what retail would spend, so L+R then A is the retail summon. The slices of the bars you spend are lit in the wheel's colours, the ones you have but keep are dotted, the ones you do not have are dark. Only your own fighter gets the popup; the opponent summons as before.

The bit beast fills 0x20 of its 0x2400 capacity per battle tick (`sub_08032A88`). A part bar left over by the choice stays too, e.g. 2.5 bars with one spent leaves 1.5.

With the debug menu's **Start Full Gauge** the gauge is full at launch, which makes this easy to try.

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Popup** | `Choose` in [`bars.c`](src/bars.c) | Own frame loop (`VBlankIntrWait`), reads `REG_KEYINPUT` directly |
| **Picture** | `DrawPicture`, `DrawWheel`, `Put` in [`bars.c`](src/bars.c) | 128x128 pixels drawn into a buffer in OBJ tile layout, shown as four 64x64 sprites |
| **Take over / put back** | `Plan`, `Open`, `Close` in [`bars.c`](src/bars.c) | Picks an OBJ palette bank and 256 OBJ tiles no visible sprite uses, shifts the game's sprites up four OAM entries (order kept), darkens every other colour, and puts all of it back |
| **Bars** | `BitBeastBars` in [`bars.c`](src/bars.c), [`thunk.s`](src/thunk.s) | Replaces the `bl` to the division in the summon code (`call 0x08034D84`); the thunk passes the fighter (r4) |
| **Unspent gauge** | `BitBeastSummonStart` in [`bars.c`](src/bars.c) | Replaces the `bl` that starts the summon sequence (`call 0x08034DC0`) and puts the rest of the gauge back |
| **Damage** | `BitBeastBars`, `sHits` in [`bars.c`](src/bars.c) | Attack + defense + endurance of your blade times the number of hits |
| **State** | [`ram.s`](src/ram.s) | `gBars` at `0x02038000`, 28 KB below the shared mod page |

How it works in the retail code: the fighter handler `sub_08034BE0` (called for both fighters each frame) tests `(fighter + 0x302) & 0x300 == 0x300` (L and R in the input mask) and, when the gauge reading `fighter + 0x2F0` divided by 12 is not zero and no summon is running (`sub_080342C8`), zeroes `BattleWork + 0xBBC + index * 4` (the gauge), starts the sequence (`sub_08034090`) and stores the bars at `BattleWork + 0x20D5`, which `sub_08034250` turns into the animation (1, 2 or 3).

---

## 📝 TODO

- Show the popup in the opponent's summon? (not needed, the opponent does not choose)
- Try it on a real console, the checks below are all in mGBA

---

## 🐛 Limitations & Bugs

- Checked in mGBA: the popup, left / right / A / B, the 1, 2 and 3 bar summons and the gauge left over, with the retail ROM's first (tutorial) battle. Not played through a whole fight, and not on hardware.
- While the popup is open the game itself is stopped, but music keeps playing.
- The popup is drawn over the game's sprites with OAM entries 0 to 3 (the game's own entries shift up four and back, so their drawing order is unchanged; the last four must be hidden ones, which they are in the battles checked), OBJ tiles and a palette bank that no visible sprite uses. It does not use the game's own allocators, so it does not clash with them.
- The damage is an estimate. Each hit of the beast takes attack + defense + endurance of your blade off the opponent (checked: 9 + 6 + 11 = 26 per hit), but the number of hits comes from the beast animation and where the blades are, about 12, 23 and 35 for one, two and three bars. Blocks or a knocked-out opponent are not modelled.
- The debug menu's **Max RPM** sets the gauge capacity (`BattleWork + 0xBC4`) to 32767 along with the RPM, so the gauge then refills far more slowly than the retail 0x2400. That is the debug menu's doing, not this mod's.

---
