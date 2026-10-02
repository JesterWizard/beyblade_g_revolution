"""Find the dialogue portraits in the ROM and the palette each one is shown with.

A portrait is a 64x32, single-frame, 4bpp sprite template (see sprite.py).
Conversation scripts select one with a `template, palette` pointer pair
(`08266DAC 0826E320`, opcode 0x1D in the event streams around 0x099000), so
the palette is whatever follows the template pointer. Three more sources pair
the ones scripts do not mention:

  * the actor tables behind `BeybladeGetActorSprite` / `BeybladeGetActorPalette`
    (sprites at 0x08091004, palettes at 0x080910E8, indexed by Beyblade id);
  * code literal pools shaped `template, 0xFFFFC000, palette` (the sprite is
    created off-screen, then its palette is copied to OBJ palette RAM);
  * last resort: portraits are stored back to back and their palettes are
    512-byte blocks stored in the same order, so a template with no pair takes
    the block right after its neighbour's.
"""

import re
import struct

from gba import GfxError, palette_looks_valid
from sprite import load_sprite

ROM_BASE = 0x08000000
ACTOR_SPRITES = 0x091004
ACTOR_PALETTES = 0x0910E8
ACTOR_COUNT = 55
OFFSCREEN = 0xFFFFC000
BLOCK = 0x200
NEIGHBOUR = 0x400  # max gap between back-to-back portrait templates

# 64x32 template header: +4 w, +5 h, (+6, +7 vary), +8 u32 1.
_SIG = re.compile(b"\x40\x20..\x01\x00\x00\x00", re.S)


def find_templates(rom):
    """ROM offsets of every single-frame 64x32 4bpp sprite template that decodes."""
    found = []
    for m in _SIG.finditer(rom):
        off = m.start() - 4
        if off < 0 or off % 4 or off + 0x60 > len(rom):
            continue
        if struct.unpack_from("<I", rom, off)[0] != 1:
            continue
        try:
            tpl = load_sprite(rom, off)
            if not tpl.is_4bpp or not tpl.frame_table:
                continue
            tpl.frame_tiles(0)
        except GfxError:
            continue
        found.append(off)
    return found


def _ptr_to_off(value):
    off = value - ROM_BASE
    return off if 0 <= off < 0x2000000 else None


def _valid_palette(rom, value):
    off = _ptr_to_off(value)
    return off is not None and off + 32 <= len(rom) and palette_looks_valid(rom, off, 16)


def pair_palettes(rom, templates):
    """{template offset: palette offset} from every pairing source above."""
    tset = {ROM_BASE + t: t for t in templates}
    words = struct.unpack("<%dI" % (len(rom) // 4), rom[:len(rom) // 4 * 4])
    votes = {}

    def vote(tptr, pptr):
        if tptr in tset and _valid_palette(rom, pptr):
            votes.setdefault(tset[tptr], {}).setdefault(pptr - ROM_BASE, 0)
            votes[tset[tptr]][pptr - ROM_BASE] += 1

    for i in range(len(words) - 2):
        if words[i] in tset:
            vote(words[i], words[i + 1])
            if words[i + 1] == OFFSCREEN:
                vote(words[i], words[i + 2])
    for i in range(ACTOR_COUNT):
        s = struct.unpack_from("<I", rom, ACTOR_SPRITES + 4 * i)[0]
        p = struct.unpack_from("<I", rom, ACTOR_PALETTES + 4 * i)[0]
        vote(s, p)

    pal = {t: max(c.items(), key=lambda kv: kv[1])[0] for t, c in votes.items()}

    # Palette blocks come in template order: fill gaps from the neighbour's.
    claimed = set(pal.values())
    ordered = sorted(templates)
    changed = True
    while changed:
        changed = False
        for i, t in enumerate(ordered):
            if t in pal:
                continue
            for j, step in ((i - 1, BLOCK), (i + 1, -BLOCK)):
                if not 0 <= j < len(ordered) or ordered[j] not in pal:
                    continue
                if abs(ordered[j] - t) >= NEIGHBOUR:
                    continue
                guess = pal[ordered[j]] + step
                if guess in claimed or not _valid_palette(rom, ROM_BASE + guess):
                    continue
                pal[t] = guess
                claimed.add(guess)
                changed = True
                break
    return pal


def discover(rom):
    """[(template offset, palette offset)] sorted by template; unpaired ones are dropped."""
    templates = find_templates(rom)
    pal = pair_palettes(rom, templates)
    skipped = [t for t in templates if t not in pal]
    return sorted((t, pal[t]) for t in templates if t in pal), skipped
