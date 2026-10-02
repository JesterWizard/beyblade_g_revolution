# Thought Bubbles

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

Pressing **L** on the overworld (towns and the world map) shows or hides a 128x64 bubble above the player's head. It follows the player as they walk and the camera scrolls.

The picture follows the latest story event flag that [`bubbles.txt`](bubbles.txt) lists. With none set it shows `DEFAULT`. The bubble is hidden during dialogue, menus and map transitions (`unk180C != 0` or `unk185A != 1`, the Start menu's own test).

The latest flag is found by comparing the 256 event flags with last frame's, so no hook on `EventFlagOp` is needed. When several are set at once (loading a save) the one lowest in `bubbles.txt` wins, so list flags in story order. Flags the table does not list never change the bubble. If the latest flag is cleared, the last listed flag still set is used.

---

## 🛠️ How To Use

- Build: `make` (it is a default mod, built together with `debug_menu`), or `make MOD=thought_bubbles`.
- Press **L** on the overworld to toggle the bubble.

Adding a bubble:

1. Draw `assets/<name>.png`, 128x64. Indexed with at most 16 colours (index 0 transparent), or any RGBA image (transparent stays clear, the rest is cut to 15 colours).
2. In `bubbles.txt`, register it (`image <ID> <name>`) and map a flag to it (`flag <number> <ID>`).
3. `make`. No C changes.

The art is the ygodm8 set. Its flag 0x2B is that game's Millennium Necklace event, so repoint it at a real Beyblade event.

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Per-frame tick** | `BubbleFieldTick` in [`bubbles.c`](src/bubbles.c) | Entry point from the hook; toggles on L, tracks flags, positions the bubble |
| **Latest flag** | `TrackFlags` in [`bubbles.c`](src/bubbles.c) | Diffs the 256 event flags against last frame |
| **Graphics** | `LoadGfx`, `GfxIntact` in [`bubbles.c`](src/bubbles.c) | Copies the picture to OBJ tiles and palette, and restores it if a map load wipes it |
| **Placement** | `BubbleOrigin`, `SetOam` in [`bubbles.c`](src/bubbles.c) | Screen position from the player and camera, and the two OAM entries |
| **State** | `gBubble` in [`ram.s`](src/ram.s) | At `0x0203F800`, the second half of the EWRAM page `debug_menu` also uses |
| **Art converter** | [`gen_bubbles.py`](tools/gen_bubbles.py) | Turns each picture into two 64x64 4bpp OBJ halves plus a 16-colour palette; run by [`mod.mk`](mod.mk) |
| **Hook** | `call 0x080470F4` in [`hooks.txt`](hooks.txt) | The `CursorHistoryReplayStep` call in `FieldUpdateFrame`; `debug_menu` keeps the `HudRefreshStats` call |
| **Heap patch** | `patch 0x0806A3DE` / `0x0806A622` in [`hooks.txt`](hooks.txt) | Shrinks the heap to free the state page; identical to `debug_menu`'s patch, applied once |

Hardware used: OAM entries 126-127, OBJ tiles 0x380-0x3FF, OBJ palette slot 12, priority 0 (in front). The engine hands these out last, and the overworld uses well under half (about 27 entries, 464 tiles).

---

## 📝 TODO

- Point the flag table at real Beyblade story events
- Draw Beyblade-specific bubble art

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Checked in the emulator on a town map; not looked at on the 16-node world map screen, which runs the same `FieldUpdateFrame`.
- The shipped art is from another game (ygodm8) and its flag is a placeholder.

---
