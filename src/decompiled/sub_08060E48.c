#include "global.h"
#include "ram_map.h"
#include "battle.h"

void TextWindowPutChar(void *arg, u32 chArg)
{
    struct TextWindow *w = arg;
    u8 ch = chArg;
    u16 gw;
    u16 rows;
    u32 *glyph;

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
    {
        s32 xt = ((s16)w->penX >> 3) << 5;
        s32 yt = (s16)w->penY >> 3;
        u32 unkA6 = w->unkA6;
        u32 sx = w->penX & 7;
        u8 *mapBase = (u8 *)0x06000000 + (w->screenBlock << 11);
        u32 shl = sx * 4;

        do
        {
            u8 *tile = (u8 *)0x06000000 + xt + (w->charBlock << 14) + ((w->width >> 3) << 5) * yt;
            u16 *map = (u16 *)(mapBase + ((yt + unkA6) << 6));
            s32 col = w->unkA4;
            u32 left = gw;
            u32 *t;

            rows -= 8;
            yt++;
            t = (u32 *)tile;
            do
            {
                u32 k;

                map[((s16)w->penX >> 3) + col] &= 0xFFF;
                map[((s16)w->penX >> 3) + col] |= w->baseTile;
                if (sx != 0)
                {
                    map[((s16)w->penX >> 3) + col + 1] &= 0xFFF;
                    map[((s16)w->penX >> 3) + col + 1] |= w->baseTile;
                }
                for (k = 0; k < 4; k++)
                {
                    u32 v = *glyph++;
                    t[0] |= v << shl;
                    t[8] |= v >> ((8 - sx) * 4);
                    t++;
                    v = *glyph++;
                    t[0] |= v << shl;
                    t[8] |= v >> ((8 - sx) * 4);
                    t++;
                }
                left -= 8;
                col++;
            } while (left != 0);
        } while (rows != 0);
        w->penX += gw - ((u8 *)w->widthTable)[ch];
    }
}
