"""Decoder for the game's LZ77-compressed background container.

Layout (little-endian u32 words; offsets are relative to the container, which
is the *decompressed* stream). It is the structure `AffineBgLoad` reads
(`struct AffineBgResource` in include/unknown-types.h):

    +00  total size (decompressed bytes + trailing palette)
    +04  tile data offset (always 0x20)
    +08  tile data size
    +0C  tilemap offset
    +10  tilemap size
    +14  unk14
    +18  u8 shape, +19 u8 flags (bit 0 set = 4bpp, clear = 8bpp)
    +1C  u16 map width in tiles, +1E u16 map height in tiles

The tilemap is row-compressed: a table of one u32 byte offset per row, each
pointing at `u16 payload_bytes` followed by that many bytes of items:

    s16 n < 0   skip -n cells (transparent)
    s16 n > 0   n literal u16 tilemap entries follow

A tilemap entry is the usual text-BG one: bits 0-9 tile, 10 hflip, 11 vflip,
12-15 palette bank (4bpp only).

The palette is not part of the container. For every full-screen image and the
interior maps it is the 512 bytes stored right after the compressed stream.
"""

import struct

from gba import GfxError, lz77_decompress, palette_looks_valid, read_palette, write_indexed_png


class BgResource(object):
    def __init__(self, data):
        if len(data) < 0x20:
            raise GfxError("BG container shorter than its header")
        (self.total, self.tiles_off, self.tiles_size, self.map_off, self.map_size,
         self.unk14, self.shape_flags, self.dims) = struct.unpack_from("<8I", data, 0)
        self.data = data
        self.width = self.dims & 0xFFFF
        self.height = self.dims >> 16
        self.is_4bpp = bool((self.shape_flags >> 8) & 1)
        self.tile_bytes = 32 if self.is_4bpp else 64
        if self.tiles_off != 0x20 or self.tiles_size == 0 or self.map_size < 4:
            raise GfxError("not a tiled BG container")
        if not (0 < self.width <= 128 and 0 < self.height <= 128):
            raise GfxError("implausible map size %dx%d" % (self.width, self.height))
        if self.tiles_off + self.tiles_size > len(data) or self.map_off + self.map_size > len(data):
            raise GfxError("BG container sections overrun the stream")

    @property
    def tiles(self):
        return self.data[self.tiles_off:self.tiles_off + self.tiles_size]

    def map_cells(self):
        """Tilemap as rows of entries; None where the row skips the cell."""
        m = self.data[self.map_off:self.map_off + self.map_size]
        rows = struct.unpack_from("<I", m, 0)[0] // 4
        if rows < self.height:
            raise GfxError("tilemap has %d rows, header says %d" % (rows, self.height))
        offsets = struct.unpack_from("<%dI" % rows, m, 0)
        grid = []
        try:
            for y in range(self.height):
                row = [None] * self.width
                p = offsets[y]
                end = p + 2 + struct.unpack_from("<H", m, p)[0]
                p += 2
                x = 0
                while p < end:
                    n = struct.unpack_from("<h", m, p)[0]
                    p += 2
                    if n < 0:
                        x += -n
                        continue
                    for _ in range(n):
                        row[x] = struct.unpack_from("<H", m, p)[0]
                        p += 2
                        x += 1
                grid.append(row)
        except (struct.error, IndexError):
            raise GfxError("malformed row-compressed tilemap")
        return grid

    def render(self):
        """Full image as (width_px, height_px, palette-index bytes).

        4bpp images carry their palette bank in the index (bank*16 + colour),
        so every image maps onto a single 256-entry palette.
        """
        tiles = self.tiles
        tsz = self.tile_bytes
        ntiles = len(tiles) // tsz
        w = self.width * 8
        h = self.height * 8
        pix = bytearray(w * h)
        for ty, row in enumerate(self.map_cells()):
            for tx, e in enumerate(row):
                if e is None:
                    continue
                t = e & 0x3FF
                if t >= ntiles:
                    continue
                hflip = e >> 10 & 1
                vflip = e >> 11 & 1
                bank = (e >> 12) * 16 if self.is_4bpp else 0
                base = t * tsz
                for y in range(8):
                    sy = 7 - y if vflip else y
                    dst = (ty * 8 + sy) * w + tx * 8
                    if self.is_4bpp:
                        src = base + y * 4
                        for i in range(4):
                            b = tiles[src + i]
                            lo = b & 15
                            hi = b >> 4
                            if hflip:
                                pix[dst + 7 - 2 * i] = lo + bank if lo else 0
                                pix[dst + 6 - 2 * i] = hi + bank if hi else 0
                            else:
                                pix[dst + 2 * i] = lo + bank if lo else 0
                                pix[dst + 2 * i + 1] = hi + bank if hi else 0
                    else:
                        src = base + y * 8
                        px = tiles[src:src + 8]
                        pix[dst:dst + 8] = px[::-1] if hflip else px
        return w, h, pix


def load_bg(rom, off):
    """Decompress and parse the container at `off`. Returns (BgResource, end)."""
    data, end = lz77_decompress(rom, off)
    return BgResource(data), end


def palette_after(rom, end):
    """ROM offset of the 512-byte palette that follows a stream ending at `end`,
    or None if what follows does not look like one."""
    off = (end + 3) & ~3
    return off if palette_looks_valid(rom, off) else None


def write_bg_png(rom, res, pal_off, path):
    """Render `res` with the 256-colour palette at `pal_off` into a PNG."""
    w, h, pix = res.render()
    palette = read_palette(rom, pal_off, 256)
    if res.is_4bpp:
        transparent = set(range(0, 256, 16))
    else:
        transparent = {0}
    write_indexed_png(path, w, h, pix, palette, transparent)
    return w, h
