# Fast Save

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

Saving takes several seconds on real hardware. A save slot is 0x1F60 bytes, which is 1004 data blocks plus 3 header blocks of 8 bytes, and retail programs every one of them and reads it back to verify. Each EEPROM program cycle takes several milliseconds, but between two saves almost every block is identical.

This mod reads each block first (microseconds) and only writes it when it differs from what the chip holds. The retail verify and 8-retry logic after each block is untouched, so a failed write is still detected.

The aim is to ensure:

- A typical save writes a small fraction of the blocks
- A block that differs, or cannot be read, is still written by the retail routine
- The save data on the chip ends up byte-identical to a retail save

---

## 🛠️ How To Use

```
make MOD=fast_save                               # only this mod
make                                             # all default mods, this one included
```

Nothing to configure: save as usual. It is enabled by `MOD_FAST_SAVE` in `mods/mods.h`, so plain `make` includes it.

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Skip unchanged block** | `FastSaveWriteBlock` in [`fast_save.c`](src/fast_save.c) | Calls `EepromVerifyBlock` (`sub_080677A8`) and returns when the block already matches, else calls `EepromWriteBlock` (`sub_08067634`) |
| **Header blocks hook** | `call 0x08044D54` in [`hooks.txt`](hooks.txt) | The `bl EepromWriteBlock` in `sub_08044D2C`, which writes the 3 header blocks of a slot |
| **Data blocks hook** | `call 0x08044F30` in [`hooks.txt`](hooks.txt) | The `bl EepromWriteBlock` in `sub_08044F14`, which writes the slot's 1004 data blocks |

---

## 📝 TODO

- Measure blocks written per save on a real save file
- Cover `SaveSlotWriteDefault` (`src/save.c`), which resets a corrupt slot

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Emulators write EEPROM instantly, so the gain only shows on real hardware or a timing-accurate setup.
- Built and checked against the retail disassembly only; not yet run in an emulator or on a cartridge.
- `SaveSlotWriteDefault` is not hooked (it is compiled C, not the asm loops above), so resetting a corrupt slot is as slow as retail.

---
