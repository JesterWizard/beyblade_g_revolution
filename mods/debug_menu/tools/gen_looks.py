#!/usr/bin/env python3
"""Generate src/character_looks.c: every distinct person sprite in the game.

The game draws each scene NPC (table at 0x0807BE04, one row per NPC id) with
the template in the row and the palette gData_080775CC[id] (0x080775CC); this
lists every distinct (template, palette) pair of the 15- to 31-frame person
sprites, in id order, with the NPC ids that use it.

Names: the ROM does not say who an NPC is. Kai, Kenny, Max and Daichi are
picked by eye (MAIN below), a few more come from NAMES; everything else is "NPC <id>" with Tyson's
portrait. Add an entry to MAIN (name/portrait index -> NPC id) to name another.

usage: gen_looks.py <rom.gba> <ow.state> <out.c> [preview.png]
"""
import os, shutil, struct, sys, tempfile, colorsys
sys.path.insert(0, "tools/mod/emu")
from emu import Emu
from PIL import Image

rom_path, state, out = sys.argv[1:4]
preview = sys.argv[4] if len(sys.argv) > 4 else None
rom = open("baserom.gba", "rb").read()
def rw(a): return struct.unpack_from("<I", rom, a - 0x08000000)[0]
def pal(a): return [struct.unpack_from("<H", rom, a - 0x08000000 + 2 * i)[0] for i in range(16)]
def to8(c): return tuple(((v & 31) << 3) | ((v & 31) >> 2) for v in (c, c >> 5, c >> 10))
def hsv(c): return colorsys.rgb_to_hsv(*(x / 255 for x in c))
def is_skin(c):
    h, s, v = hsv(c); return 0.0 <= h <= 0.12 and 0.2 <= s <= 0.65 and v >= 0.5
def is_neutral(c):
    h, s, v = hsv(c); return s < 0.18 or v < 0.2
def dist(a, b): return sum((x - y) ** 2 for x, y in zip(a, b)) ** 0.5

MAIN = {0: 1, 1: 2, 2: 3, 3: 4, 4: 5, 5: 6, 6: 7, 7: 13, 8: 14, 9: 15, 10: 16, 11: 17, 12: 39, 13: 38, 14: 47, 15: 48, 16: 49, 17: 50, 18: 51, 19: 25, 20: 34, 21: 67, 22: 68, 23: 69, 24: 70, 25: 71, 26: 72, 27: 95, 28: 55, 29: 111, 30: 73, 31: 26, 32: 117, 33: 118, 34: 119, 35: 120, 36: 142, 37: 143, 38: 147, 39: 148, 40: 149, 41: 150, 42: 154, 43: 155, 44: 156, 45: 164, 46: 165, 47: 172, 48: 185, 49: 186, 50: 187, 51: 179, 53: 222}   # blader portrait index -> NPC id (matched by eye, see README)
# NPC id -> name for sprites with no blader portrait (from the player's own knowledge of the game)
NAMES = {0: "Grandpa", 8: "Lyn", 9: "Keiko", 10: "Katy", 11: "Jasmine", 13: "Bonz", 33: "Jin of the Gale"}
# NPC id -> (portrait template, palette) of a dialogue portrait that is not a blader's (matched by eye)
EXTRA = {0: (0x0827A520, 0x08275520), 8: (0x0827A71C, 0x08275720), 9: (0x0827A91C, 0x08275920), 10: (0x0827AAC8, 0x08275B20), 11: (0x0827ACDC, 0x08275D20), 12: (0x0827AF10, 0x08275F20), 18: (0x0827B144, 0x08276120), 19: (0x0827B32C, 0x08276320), 20: (0x0827B4E8, 0x08276520), 21: (0x0827B700, 0x08276720), 22: (0x0827B914, 0x08276920), 23: (0x0827BB1C, 0x08276B20), 24: (0x0827BCDC, 0x08276D20), 27: (0x0827BEBC, 0x08276F20), 33: (0x0827C0C0, 0x08277120), 37: (0x0827C6FC, 0x08277720), 43: (0x0827C320, 0x08277320), 56: (0x0827D6AC, 0x08278720), 78: (0x0827DC4C, 0x08278D20), 92: (0x0827DFD4, 0x08279120), 177: (0x0827E7E8, 0x08279920), 178: (0x0826DC1C, 0x08274D20), 188: (0x0827E210, 0x08279320), 189: (0x0827E424, 0x08279520), 191: (0x0827E63C, 0x08279720), 207: (0x0827EC38, 0x08279D20), 215: (0x0827EE54, 0x08279F20), 216: (0x0827F074, 0x0827A120), 220: (0x0827F294, 0x0827A320), 244: (0x08317C94, 0x08317894), 245: (0x08317E5C, 0x08317A94)}
HUMANS = list(range(28))
FRAMES = (12, 15, 17, 29, 31)
HERO = (0x083147C8, 0x083002E0)

_sav = tempfile.mktemp(suffix=".sav"); shutil.copy("beyblade_g_revolution.sav", _sav)
e = Emu(rom_path, _sav)
OBJ = 0x02000804 + 0x36C

def hide_bg():
    e.w16(0x04000000, e.r16(0x04000000) & ~0x0F00); e.w16(0x05000000, 0x7C1F)

def _unused(im, lookup=None):
    px = [(x, y, im.getpixel((x, y))) for y in range(im.height) for x in range(im.width)
          if im.getpixel((x, y)) != (255, 0, 255)]
    px = [q for q in px if lookup is None or q[2] in lookup]
    if not px: return None
    ys = [q[1] for q in px]; y0, y1 = min(ys), max(ys); h = max(1, y1 - y0)
    def dom(sel):
        cnt = {}
        for x, y, c in px:
            if sel(y, c): cnt[c] = cnt.get(c, 0) + 1
        return max(cnt, key=cnt.get) if cnt else None
    hair = dom(lambda y, c: y < y0 + 0.4 * h and not is_skin(c) and not is_neutral(c))
    outfit = dom(lambda y, c: y > y0 + 0.5 * h and not is_skin(c) and not is_neutral(c))
    return hair or (80, 60, 40), outfit or (120, 60, 60)

# 1. distinct person sprites
pairs = {}
for i in range(246):
    t = rw(0x0807BE04 + 0x1c * i + 0x10); p = rw(0x080775CC + 4 * i)
    if 0x08200000 <= t < 0x08320000 and rw(t + 4) == 0x9a082010 and 0x08000000 <= p < 0x08400000 \
            and rw(t) in FRAMES and (t, p) != HERO:
        pairs.setdefault((t, p), []).append(i)
order = sorted(pairs, key=lambda k: pairs[k][0])
print(len(order), "distinct person sprites")

# 2. names
name_of = {}                       # (t, p) -> name index
for idx, npc in MAIN.items():
    t = rw(0x0807BE04 + 0x1c * npc + 0x10); p = rw(0x080775CC + 4 * npc)
    name_of[(t, p)] = idx
named = sorted((k for k in order if k in name_of), key=lambda k: name_of[k])
rest = [k for k in order if k not in name_of]
final = named + rest

with open(out, "w") as f:
    f.write("/* Generated by mods/debug_menu/tools/gen_looks.py; do not edit. Every person\n"
            " * sprite the game draws: walking sprite template, its palette, the blader\n"
            " * portrait / name index (56 = none, the player's), and the lowest NPC id that\n"
            " * uses it, a dialogue portrait template and palette for NPCs that are not\n"
            " * bladers (0 = none), and a name (\"NPC <id>\" is shown when there is none). */\n"
            "#include \"debug_menu.h\"\n\n"
            "const struct CharacterLook gCharacterLooks[CHARACTER_COUNT] = {\n")
    for k in final:
        nm = next((NAMES[i] for i in pairs[k] if i in NAMES), None)
        ft, fp = next((EXTRA[i] for i in pairs[k] if i in EXTRA), (0, 0))
        f.write("    {0x%08X, 0x%08X, %d, %d, %s, 0x%08X, 0x%08X},\n" % (k[0], k[1], name_of.get(k, 56), pairs[k][0],
                                                                 '"%s"' % nm if nm else "0", ft, fp))
    f.write("};\n")
with open(os.path.join(os.path.dirname(out), "..", "include", "character_count.h"), "w") as f:
    f.write("/* Generated by gen_looks.py. */\n#define CHARACTER_COUNT %d\n" % len(final))
for k in final: print(hex(k[0]), hex(k[1]), name_of.get(k, "-"), pairs[k])

if preview:
    tiles = []
    for k in final:
        e.load(state); e.frames(2)
        e.call(0x08068809, OBJ); e.w32(OBJ, k[0]); e.call(0x08068419, OBJ); e.call(0x08067CE9, OBJ, 0)
        for j, v in enumerate(pal(k[1])): e.w16(0x05000200 + 2 * j, v)
        e.frames(2, "DOWN"); e.frames(8); e.shot("/tmp/_p.png", scale=1)
        tiles.append(Image.open("/tmp/_p.png").convert("RGB").crop((108, 126, 140, 166)).resize((64, 80), Image.NEAREST))
    cols = 14
    sheet = Image.new("RGB", (64 * cols, 80 * ((len(tiles) + cols - 1) // cols)))
    for n, t_ in enumerate(tiles): sheet.paste(t_, ((n % cols) * 64, (n // cols) * 80))
    sheet.save(preview)
