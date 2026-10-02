# thought_bubbles

**L** on the overworld (towns and the world map) shows or hides a 128x64 bubble
above the player's head, following it as it walks and the camera scrolls. The picture follows the latest story event flag that
`bubbles.txt` lists; with none set it shows `DEFAULT`. `src/bubbles.c`. A separate mod; plain `make` builds it together with `debug_menu`.

Adding a bubble:

1. Draw `assets/<name>.png`, 128x64. Indexed with at most 16 colours
   (index 0 transparent), or any RGBA image (transparent stays clear, the rest is
   cut to 15 colours).
2. In `bubbles.txt`, register it (`image <ID> <name>`) and map a flag to it
   (`flag <number> <ID>`).
3. `make`. No C changes.

The art is the ygodm8 set. Its flag 0x2B is that game's Millennium Necklace
event, so repoint it at a real Beyblade event.

- `tools/gen_bubbles.py` (run by `mod.mk`) turns each picture into two 64x64 OBJ
  halves, 4bpp, plus a 16-colour palette.
- The latest flag is found by comparing the 256 event flags with last frame's, so
  no hook on `EventFlagOp` is needed. Several set at once (loading a save): the
  one lowest in `bubbles.txt` wins, so list flags in story order. Flags the table
  does not list never change the bubble. If the latest flag is cleared, the last
  listed flag still set is used.
- Drawn with OAM entries 126-127, OBJ tiles 0x380-0x3FF and OBJ palette slot 12,
  priority 0 (in front). The engine hands these out last, and the overworld uses
  well under half (about 27 entries, 464 tiles). The picture is verified each
  frame and restored if a map load wipes it. State is `gBubble` at `0x0203F800`, the second half of the EWRAM page `debug_menu` also uses.
- Hooks the `CursorHistoryReplayStep` call in `FieldUpdateFrame` (0x080470F4); `debug_menu` keeps the `HudRefreshStats` call. Both make the same heap `patch`, which is applied once.
- Hidden during dialogue, menus and map transitions (`unk180C != 0` or
  `unk185A != 1`, the Start menu's own test).
- Checked in the emulator on a town map; not looked at on the 16-node world map
  screen, which runs the same `FieldUpdateFrame`.
