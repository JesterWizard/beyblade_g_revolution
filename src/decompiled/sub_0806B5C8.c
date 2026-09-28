/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void sub_0806B5C8(u16 *tiles, s32 base, u32 *src, s32 x, u32 y)
{
    u32 *tl, *tr, *bl, *br;
    s32 col;
    s32 shl, shr;
    s32 n;
    u32 w, lo, hi;

    col = x >> 3;
    if (y > 0x98 || (u32)(x + 7) > 0xF6)
        return;
    tl = (u32 *)sub_0806B5B8(base, tiles[0]);
    tr = (u32 *)sub_0806B5B8(base, tiles[1]);
    bl = (u32 *)sub_0806B5B8(base, tiles[0x20]);
    br = (u32 *)sub_0806B5B8(base, tiles[0x21]);
    x &= 7;
    y &= 7;
    tl += y;
    tr += y;
    shl = x * 4;
    shr = 32 - shl;
    n = 8 - y;
    while (n--)
    {
        w = *src++;
        lo = w << shl;
        hi = w >> shr;
        if (col >= 0)
            *tl |= lo;
        if (col <= 28)
            *tr |= hi;
        tl++;
        tr++;
    }
    n = y;
    while (n--)
    {
        w = *src++;
        lo = w << shl;
        hi = w >> shr;
        if (col >= 0)
            *bl |= lo;
        if (col <= 28)
            *br |= hi;
        bl++;
        br++;
    }
}
