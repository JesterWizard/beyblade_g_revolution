# Keep Blade

## 🧩 Introduction

In retail, losing a battle can cost you the BeyBlade you fought with (it is removed from your inventory). This mod makes a loss never take it, in any battle mode. Wins and draws are unchanged, and so is the wear on your parts.

## 🛠️ How To Use

```
make MOD=keep_blade     # only this mod
make                    # all default mods, this one included
```

It is enabled by `MOD_KEEP_BLADE` in [`mods/mods.h`](../mods.h); set it to 0 to get the retail penalty back. The debug menu's "Inf. BeyBlade Health" entry does the same thing behind a toggle and can be used alongside this mod (the two patch different bytes).

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Spare on loss** | `patch 0x080380FC` in [`hooks.txt`](hooks.txt) | In the battle result `sub_08037F98` a loss already jumps to a "spare" exit (`0x08038144`) for battle modes 11, 8, 7, 10 and 9. Every other mode falls through to the code that takes the blade; its first instruction (`movs r0, #1`) becomes `b 0x08038144` |

## 🐛 Limitations & Bugs

- Checked only by reading the patched branch (it lands on the same exit the retail mode checks use) and by building with the debug menu's hook alongside. Not played through a lost battle in the emulator.
