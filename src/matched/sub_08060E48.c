#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060e48
/* match-compiler: old_agbcc */
// Draw one glyph of `chArg` at the window's pen: point the tilemap cells the
// glyph covers at the window's tiles (baseTile palette bits), OR the 4bpp glyph
// rows into the tile graphics shifted by the pen's sub-tile x offset (spilling
// into the next tile column), then advance penX. A space only advances by
// `spacing`; glyphs that would cross the window edge are skipped.
void TextWindowPutChar(struct TextWindow *w, u32 chArg)
{
    u8 ch;
    u32 sx;
    s32 xt;
    u32 unkA6;
    u32 *glyph;
    u32 mapBase;
    u32 gw;
    u32 rows;
    s32 yt;

    ch = chArg;
    if (ch == 0x20)
    {
        w->penX += w->spacing;
        return;
    }
    gw = w->glyphWidth;
    rows = w->lineHeight;
    ch = gData_080BB748[ch];
    glyph = sub_0806BB38(w->unk88, ch);
    if ((u32)((s16)w->penX + (gw - ((u8 *)w->widthTable)[ch])) >= w->width)
        return;
    if ((s16)w->penY >= w->height)
        return;
    if (w->lineHeight + (s16)w->penY >= w->height)
        return;

    xt = ((s16)w->penX >> 3) << 5;
    yt = (s16)w->penY >> 3;
    unkA6 = w->unkA6;
    sx = w->penX & 7;
    mapBase = 0x06000000 + (w->screenBlock << 11);

    do
    {
        u32 *t = (u32 *)((u8 *)(w->charBlock << 14) + (xt + 0x06000000) + ((w->width >> 3) << 5) * yt);
        s32 col = w->unkA4;

        do
        {
            u32 k;
            u16 *map = (u16 *)(((yt + unkA6) << 6) + mapBase);

            map[((s16)w->penX >> 3) + col] &= 0xFFF;
            map[((s16)w->penX >> 3) + col] |= w->baseTile;
            if (sx != 0)
            {
                map[((s16)w->penX >> 3) + col + 1] &= 0xFFF;
                map[((s16)w->penX >> 3) + col + 1] |= w->baseTile;
            }
            for (k = 0; k < 4; k++)
            {
                u32 v, hi;
                u32 shl = sx * 4;
                u32 rsh = (8 - sx) * 4;

                v = *glyph++;
                hi = v;
                v <<= shl;
                hi >>= rsh;
                t[0] |= v;
                t[8] |= hi;
                t++;
                v = *glyph++;
                hi = v;
                v <<= shl;
                hi >>= rsh;
                t[0] |= v;
                t[8] |= hi;
                t++;
            }
            gw -= 8;
            col++;
        } while (gw != 0);
        rows -= 8;
        yt++;
        gw = w->glyphWidth;
    } while (rows != 0);
    w->penX += gw - ((u8 *)w->widthTable)[ch];
}

