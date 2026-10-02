"""Decoder for the game's OBJ sprite templates (what `SpriteInitFromTemplate` reads).

A template is a 0x20-byte header followed by an animation table, a frame
offset table and the tile data. Header (little-endian):

    +00  u32 frame count
    +04  u8 width px, +05 u8 height px, +06 u8 log2(bytes per raw frame),
    +07  u8 OAM shape/size bits; bit 7 set = tiles use the "row" codec (below)
    +0C  u8 bit 0 = 4bpp, bits 1-4 = OBJ palette bank
    +0D  u8 compressed-frame header size in bytes (4, or 8 for > 32 tiles)
    +0E  u16 tiles per frame
    +10  u32 tile data offset (from the template)
    +1C  u32 frame offset table offset; 0 = frames are stored raw

Raw frames sit at `+10 + (frame << log2size)`. Compressed frames start at
`+10 + table[frame]` with one u32 mask per 32 tiles (two when the frame has
more than 32 tiles; see `_chunks`), then the payload. The IWRAM routine at
0x030044D8 (ROM 0x083D3384 + 0x36C) expands them:

    mask bit 1  -> the tile is all zero
    mask bit 0  -> the tile is read from the payload; LSB is the first tile

Plain frames (header bit 7 clear) store those tiles verbatim. "Row" frames
(bit 7 set, 4bpp only) store each tile as eight 32-bit rows built from:

    u8 flags     bit i: row i starts a new base colour (else keep the last one)
    nibbles      ceil(popcount(flags)/2) bytes, low nibble first; a nibble n
                 means base row = n repeated eight times
    4 x u8 keys  one byte per row pair, low nibble = first row, high = second;
                 bit k replaces byte k (two pixels) of the row with a literal
    literals     one byte per set key bit, rows in order

The tile bytes are the standard GBA 1D OBJ layout (rows of width/8 tiles).
"""

import struct

from gba import GfxError, palette_looks_valid, read_palette, write_indexed_png

_NIBBLE_ROW = [0x11111111 * i for i in range(16)]


class SpriteTemplate(object):
    def __init__(self, rom, off):
        if off < 0 or off + 0x20 > len(rom):
            raise GfxError("sprite template at 0x%X is outside the ROM" % off)
        self.rom = rom
        self.off = off
        self.frames = struct.unpack_from("<I", rom, off)[0]
        self.frame_table = struct.unpack_from("<I", rom, off + 0x1C)[0]
        self.width = rom[off + 4]
        self.height = rom[off + 5]
        self.log2_frame = rom[off + 6]
        self.shape_bits = rom[off + 7]
        self.is_4bpp = bool(rom[off + 0xC] & 1)
        self.palette_bank = (rom[off + 0xC] >> 1) & 0xF
        self.header_bytes = rom[off + 0xD]
        self.tiles = struct.unpack_from("<H", rom, off + 0xE)[0]
        self.data_off = struct.unpack_from("<I", rom, off + 0x10)[0]
        self.row_codec = bool(self.shape_bits & 0x80)
        if not (0 < self.frames < 0x400):
            raise GfxError("implausible frame count %d at 0x%X" % (self.frames, off))
        if not (0 < self.width <= 64 and 0 < self.height <= 64 and self.width % 8 == 0 and self.height % 8 == 0):
            raise GfxError("implausible sprite size %dx%d at 0x%X" % (self.width, self.height, off))
        if self.frame_table and self.tiles != (self.width // 8) * (self.height // 8):
            raise GfxError("tile count %d does not match %dx%d" % (self.tiles, self.width, self.height))

    @property
    def tile_bytes(self):
        return 32 if self.is_4bpp else 64

    def frame_tiles(self, frame):
        """Decoded tile bytes of `frame` (tiles * tile_bytes long)."""
        if not 0 <= frame < self.frames:
            raise GfxError("frame %d out of range (0..%d)" % (frame, self.frames - 1))
        rom = self.rom
        base = self.off + self.data_off
        if not self.frame_table:
            size = 1 << self.log2_frame
            a = base + (frame << self.log2_frame)
            if a + size > len(rom):
                raise GfxError("raw frame overruns the ROM")
            return bytes(rom[a:a + size])
        entry = self.off + self.frame_table + frame * 4
        a = base + struct.unpack_from("<I", rom, entry)[0]
        hdr = self.header_bytes
        mask1 = struct.unpack_from("<I", rom, a)[0]
        mask2 = struct.unpack_from("<I", rom, a + 4)[0] if hdr > 4 else 0
        reader = _Reader(rom, a + (hdr & 0xFC))
        out = bytearray()
        try:
            for kind, n in _chunks(self.tiles, mask1, mask2):
                if kind == "zero":
                    out += bytes(n * self.tile_bytes)
                elif self.row_codec:
                    if not self.is_4bpp:
                        raise GfxError("row codec on an 8bpp sprite")
                    for _ in range(n):
                        out += _row_tile(reader)
                else:
                    out += reader.take(n * self.tile_bytes)
        except (IndexError, struct.error):
            raise GfxError("compressed frame %d overruns the ROM" % frame)
        if len(out) != self.tiles * self.tile_bytes:
            raise GfxError("frame %d expanded to %d bytes, expected %d"
                           % (frame, len(out), self.tiles * self.tile_bytes))
        return bytes(out)

    def render(self, frame=0):
        """(width, height, palette-index bytes) for `frame`."""
        data = self.frame_tiles(frame)
        w, h = self.width, self.height
        tw = w // 8
        pix = bytearray(w * h)
        tsz = self.tile_bytes
        for t in range(min(len(data) // tsz, tw * (h // 8))):
            x0 = (t % tw) * 8
            y0 = (t // tw) * 8
            base = t * tsz
            for y in range(8):
                dst = (y0 + y) * w + x0
                if self.is_4bpp:
                    row = data[base + y * 4:base + y * 4 + 4]
                    for i, b in enumerate(row):
                        pix[dst + 2 * i] = b & 15
                        pix[dst + 2 * i + 1] = b >> 4
                else:
                    pix[dst:dst + 8] = data[base + y * 8:base + y * 8 + 8]
        return w, h, pix


class _Reader(object):
    def __init__(self, rom, pos):
        self.rom = rom
        self.pos = pos

    def byte(self):
        b = self.rom[self.pos]
        self.pos += 1
        return b

    def take(self, n):
        if self.pos + n > len(self.rom):
            raise IndexError
        chunk = self.rom[self.pos:self.pos + n]
        self.pos += n
        return bytes(chunk)


def _chunks(total, mask1, mask2):
    """(kind, tile count) runs for a frame, kind is "zero" or "data".

    A frame has at most two 32-tile masks. With more than 32 tiles the first
    mask covers the leading `total - 32` tiles and the second the last 32. A
    mask that runs out (all remaining bits 0) means "the rest is data".
    """
    left = total
    mask = mask1
    while left > 0:
        if mask == 0:
            n = left - 32 if left > 32 else left
            left -= n
            mask = mask2
            if n:
                yield "data", n
            continue
        ones = 0
        while mask & 1:
            ones += 1
            mask >>= 1
        if ones:
            run = ("zero", ones)
        else:
            zeros = 0
            while not mask & 1:
                zeros += 1
                mask >>= 1
            run = ("data", zeros)
        left -= run[1]
        if left == 32:
            mask = mask2
        yield run


def _row_tile(rd):
    flags = rd.byte()
    nib_bytes = (bin(flags).count("1") + 1) // 2
    nib_pos = rd.pos
    rd.pos += nib_bytes
    out = bytearray()
    base = 0
    nib_i = 0
    for _ in range(4):
        keys = rd.byte()
        for half in range(2):
            if flags & 1:
                b = rd.rom[nib_pos + nib_i // 2]
                base = _NIBBLE_ROW[(b >> 4) if nib_i & 1 else (b & 15)]
                nib_i += 1
            flags >>= 1
            row = bytearray(struct.pack("<I", base))
            for k in range(4):
                if (keys >> (4 * half + k)) & 1:
                    row[k] = rd.byte()
            out += row
    return bytes(out)


def load_sprite(rom, off):
    return SpriteTemplate(rom, off)


def write_sprite_png(rom, tpl, frame, pal_off, path):
    """Render `frame` with the palette bank at `pal_off` (16 or 256 colours)."""
    w, h, pix = tpl.render(frame)
    count = 16 if tpl.is_4bpp else 256
    if not palette_looks_valid(rom, pal_off, count):
        raise GfxError("no valid palette at 0x%X" % pal_off)
    write_indexed_png(path, w, h, pix, read_palette(rom, pal_off, count), {0})
    return w, h
