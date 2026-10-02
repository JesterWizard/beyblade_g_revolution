#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b5c8
// ORs an 8-row 4bpp glyph from `src` into the 2x2 tile block at `tiles`,
// shifted right by x & 7 pixels and down by y & 7 rows. Columns that fall
// off the left (x < 0) or right (x >> 3 > 28) edge are clipped.
void GlyphBlit2x2(u16 *tiles, s32 base, u32 *src, s32 x, u32 y)
{
    u32 *tl, *tr, *bl, *br;
    s32 col;
    s32 shr;
    s32 n, m;
    u32 lo, hi;

    col = x >> 3;
    if (y > 0x98 || (u32)(x + 7) > 0xF6)
        return;
    tl = (u32 *)TileAddrFromIndex(base, tiles[0]);
    tr = (u32 *)TileAddrFromIndex(base, tiles[1]);
    bl = (u32 *)TileAddrFromIndex(base, tiles[0x20]);
    br = (u32 *)TileAddrFromIndex(base, tiles[0x21]);
    x &= 7;
    y &= 7;
    tl += y;
    tr += y;
    x *= 4;
    shr = 32 - x;
    n = 8 - y;
    m = y;
    while (--n != -1)
    {
        hi = *src++;
        lo = hi << x;
        hi >>= shr;
        if (col >= 0)
            *tl |= lo;
        if (col <= 28)
            *tr |= hi;
        tl++;
        tr++;
    }
    while (--m != -1)
    {
        hi = *src++;
        lo = hi << x;
        hi >>= shr;
        if (col >= 0)
            *bl |= lo;
        if (col <= 28)
            *br |= hi;
        bl++;
        br++;
    }
}

