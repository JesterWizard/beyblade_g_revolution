"""Find the battle Beyblade sprites (the spinning tops seen from above).

The blade table at 0x0807A1F4 has one 0x28-byte record per Beyblade:

    +00  five pointers to the blade's name (one per language slot)
    +14  sprite template (32x32, three spin frames)
    +18  OBJ palette (16 colours)
    +1C  ..+24  battle parameters (not needed for the picture)

Both the sprite and its palette are registered in the shared sprite registry
(templates at 0x08079068, palettes at 0x08079358) that PaletteSlotAcquire reads.
"""

import re
import struct

from gba import GfxError, palette_looks_valid
from sprite import load_sprite

ROM_BASE = 0x08000000
BLADES = 0x07A1F4
STRIDE = 0x28
MAX_BLADES = 128


def _word(rom, off):
    return struct.unpack_from("<I", rom, off)[0]


def _string(rom, ptr):
    off = ptr - ROM_BASE
    if not 0 <= off < len(rom) - 64:
        return None
    raw = bytes(rom[off:off + 48]).split(b"\0")[0]
    if not raw or not all(32 <= b < 127 for b in raw):
        return None
    return raw.decode("ascii")


def _slug(name):
    return re.sub(r"[^a-z0-9]+", "_", name.lower()).strip("_")


def discover(rom):
    """([asset dicts], [(index, reason)] for records that could not be used)."""
    assets, skipped = [], []
    for i in range(MAX_BLADES):
        base = BLADES + STRIDE * i
        name = _string(rom, _word(rom, base))
        tptr, pptr = _word(rom, base + 0x14), _word(rom, base + 0x18)
        toff, poff = tptr - ROM_BASE, pptr - ROM_BASE
        try:
            if name is None or not 0 <= toff < len(rom) - 0x60:
                raise GfxError("end of table")
            tpl = load_sprite(rom, toff)
            tpl.render_sheet()
            if not tpl.is_4bpp or not palette_looks_valid(rom, poff, 16):
                raise GfxError("template or palette not usable")
        except GfxError as e:
            if str(e) == "end of table":
                break
            skipped.append((i, str(e)))
            continue
        assets.append({"name": "blade_%02d_%s" % (i, _slug(name)), "category": "beyblades",
                       "type": "sprite", "rom": "0x%06X" % toff, "palette": "0x%06X" % poff})
    return assets, skipped
