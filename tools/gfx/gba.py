"""GBA primitives: BIOS LZ77, BGR555 palettes, a dependency-free PNG writer.

Pure standard library on purpose: this runs on the first `make`, before anyone
has installed anything.
"""

import struct
import zlib


class GfxError(Exception):
    pass


def lz77_decompress(rom, off):
    """Decode a BIOS LZ77 (type 0x10) stream at `off`.

    Returns (data, end) where `end` is the offset one past the last byte the
    stream consumed. Raises GfxError if the stream is not valid LZ77.
    """
    if off < 0 or off + 4 > len(rom) or rom[off] != 0x10:
        raise GfxError("no LZ77 header at 0x%X" % off)
    size = rom[off + 1] | rom[off + 2] << 8 | rom[off + 3] << 16
    if size == 0:
        raise GfxError("empty LZ77 stream at 0x%X" % off)
    out = bytearray()
    p = off + 4
    try:
        while len(out) < size:
            flags = rom[p]
            p += 1
            for bit in range(8):
                if len(out) >= size:
                    break
                if flags & (0x80 >> bit):
                    b0 = rom[p]
                    b1 = rom[p + 1]
                    p += 2
                    length = (b0 >> 4) + 3
                    disp = ((b0 & 0xF) << 8 | b1) + 1
                    if disp > len(out):
                        raise GfxError("bad LZ77 back-reference at 0x%X" % off)
                    for _ in range(length):
                        out.append(out[-disp])
                else:
                    out.append(rom[p])
                    p += 1
    except IndexError:
        raise GfxError("truncated LZ77 stream at 0x%X" % off)
    return bytes(out[:size]), p


def read_palette(rom, off, count):
    """`count` BGR555 colours at `off` as a list of (r, g, b)."""
    colours = []
    for i in range(count):
        v = rom[off + i * 2] | rom[off + i * 2 + 1] << 8
        colours.append((
            (v & 31) * 255 // 31,
            ((v >> 5) & 31) * 255 // 31,
            ((v >> 10) & 31) * 255 // 31,
        ))
    return colours


def palette_looks_valid(rom, off, count=256):
    """True if `count` colours at `off` are plausible BGR555 (bit 15 clear)."""
    blob = rom[off:off + count * 2]
    if len(blob) != count * 2 or not any(blob):
        return False
    return all(blob[i] & 0x80 == 0 for i in range(1, len(blob), 2))


def write_indexed_png(path, width, height, pixels, palette, transparent):
    """Write an 8-bit indexed PNG.

    pixels:      bytes/bytearray, width*height palette indices
    palette:     list of (r, g, b), up to 256
    transparent: set of palette indices that get alpha 0
    """
    if len(pixels) != width * height:
        raise GfxError("pixel buffer is %d bytes, expected %d" % (len(pixels), width * height))

    def chunk(tag, body):
        crc = zlib.crc32(tag + body) & 0xFFFFFFFF
        return struct.pack(">I", len(body)) + tag + body + struct.pack(">I", crc)

    plte = b"".join(bytes(c) for c in palette)
    trns = bytes(0 if i in transparent else 255 for i in range(len(palette)))
    raw = bytearray()
    for y in range(height):
        raw.append(0)  # filter: none
        raw += pixels[y * width:(y + 1) * width]
    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 3, 0, 0, 0))
    png += chunk(b"PLTE", plte)
    png += chunk(b"tRNS", trns)
    png += chunk(b"IDAT", zlib.compress(bytes(raw), 9))
    png += chunk(b"IEND", b"")
    with open(path, "wb") as f:
        f.write(png)
