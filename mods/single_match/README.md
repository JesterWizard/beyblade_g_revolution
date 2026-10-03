# Single Match

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

Tournament matches are normally played over three bouts, and the winner is whoever has more points once three bouts are counted. This mod turns that off: the match is decided as soon as the point totals differ, so one bout is enough to win or lose.

The aim is to ensure:

- A tournament match ends after the first bout that has a winner
- A bout that ends level (equal points) still plays another bout, as retail does for a tie after three
- Nothing outside tournament matches changes (story and overworld battles are single battles already)

---

## 🛠️ How To Use

```
make MOD=single_match     # only this mod
make                      # all default mods, this one included
```

It is enabled by `MOD_SINGLE_MATCH` in [`mods/mods.h`](../mods.h); set it to 0 to get the retail best of three back.

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Decided check** | `patch 0x0802CC18` in [`hooks.txt`](hooks.txt) | Script opcode 141 (`0x0802CBFC`) sets the condition flag when the match is decided. Retail does `cmp bouts, 2; ble` and only compares the totals once more than 2 bouts are counted; the `ble` is replaced by a nop |

State used by the opcode: bout counter `MainWork+0x15C9`, player points `+0x15D0`, opponent points `+0x15D2` (both `s16`, added to by `addTournamentPoints` at `0x0802C70C` after each bout).

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Checked by calling the opcode in the emulator with set bout counts and totals (retail: decided only at 3+ bouts; patched: decided whenever the totals differ, a tie stays undecided). Not played through a real tournament, so the surrounding cutscene script ("final round" lines and the like) is unverified.
- Which bout text plays when the match ends early is whatever the script does after a decided match.

---
