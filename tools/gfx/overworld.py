"""Find the overworld sprites and the palette each one is drawn with.

Field objects come from two tables (see SceneObjSpawnList / BeybladeSpawnList):

  * NPC / scene object definitions, 0x1C bytes each from 0x0807BE04, template
    pointer at +0x10. SceneObjsUpdateAll claims the object's OBJ palette from
    the pointer table at 0x080775CC, indexed by the definition's index.
  * the Beyblade roster, 0x1C bytes each from 0x08075AB8 (62 records), sprite
    template pointer at +0x18, palette from the table at 0x080779A8 indexed by
    the Beyblade id. On the map these are small pickup icons (gems, tools, a
    fruit), so they are named `item_<id>`.

Definitions that share a template *and* palette give identical pictures, so
only the first is emitted.
"""

import struct

from gba import GfxError, palette_looks_valid
from sprite import load_sprite

ROM_BASE = 0x08000000
NPC_DEFS = 0x07BE04
NPC_PALETTES = 0x0775CC
ROSTER = 0x075AB8
ROSTER_COUNT = 62
ROSTER_PALETTES = 0x0779A8
STRIDE = 0x1C


def _word(rom, off):
    return struct.unpack_from("<I", rom, off)[0]


def _template(rom, ptr):
    off = ptr - ROM_BASE
    if not 0 <= off < len(rom) - 0x60:
        return None
    try:
        tpl = load_sprite(rom, off)
        tpl.render_sheet()
    except GfxError:
        return None
    return off if tpl.is_4bpp else None


def _palette(rom, ptr):
    off = ptr - ROM_BASE
    if 0 <= off < len(rom) - 32 and palette_looks_valid(rom, off, 16):
        return off
    return None


def discover(rom):
    """([asset dicts], [(label, reason)] for entries that could not be used)."""
    assets, skipped, seen = [], [], set()

    def add(prefix, index, tptr, pptr, category):
        tpl = _template(rom, tptr)
        pal = _palette(rom, pptr)
        label = "%s_%03d" % (prefix, index)
        if tpl is None or pal is None:
            skipped.append((label, "template 0x%08X palette 0x%08X" % (tptr, pptr)))
            return
        if (tpl, pal) in seen:
            return
        seen.add((tpl, pal))
        assets.append({"name": label, "category": category, "type": "sprite",
                       "rom": "0x%06X" % tpl, "palette": "0x%06X" % pal})

    index = 0
    while True:
        tptr = _word(rom, NPC_DEFS + STRIDE * index + 0x10)
        if _template(rom, tptr) is None:
            break
        add("npc", index, tptr, _word(rom, NPC_PALETTES + 4 * index), "overworld")
        index += 1
    for i in range(ROSTER_COUNT):
        add("item", i, _word(rom, ROSTER + STRIDE * i + 0x18),
            _word(rom, ROSTER_PALETTES + 4 * i), "overworld")
    return assets, skipped
