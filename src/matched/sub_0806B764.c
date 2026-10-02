#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b764
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b764
// Lays `str` out on a tile-map text layer starting at pixel (x, y): claims and
// clears tile cells for the aligned string width, then blits each glyph into
// them. align: 1 = right-aligned at x, 2 = centred on x. Returns the pen x.
s32 TextLayerInit(struct TextLayer *a, s32 x, s32 y, u8 *str, u32 alignArg)
{
    u8 align = alignArg;
    struct TextWindow *win = a->win;
    struct Unk6BB38 *font = a->font;
    u16 *cur = (u16 *)(0x06000000 + (win->screenBlock << 11));
    u32 charBase = 0x06000000 + (win->charBlock << 14);
    u32 wt = font->unk04 >> 3;
    u32 ht = font->unk05 >> 3;
    u32 glyphAdv = font->unk04;
    s32 strW;
    s32 rows;
    s32 cols;
    u16 start;
    u32 c;
    vu16 *reg;
    int pin; /* pins the base+offset sum so agbcc adds charBlock<<14 last */

    reg = BgGetCntReg(win->bgIndex);
    if ((*reg & 0x80) || !(font->unk0C & 1))
    {
        DebugMessage((void *)0x083D1D08);
        return x;
    }
    strW = sub_0806B724(str, a->widths, glyphAdv);
    switch (align & 3)
    {
    case 1:
        x -= strW;
        break;
    case 2:
        x -= strW >> 1;
        break;
    }
    cur += (((y & ~7) << 2) + (x >> 3));
    rows = ht;
    if ((y & 7) != 0)
        rows++;
    cols = (strW + (x & 7) + 8) >> 3;
    start = a->nextTile;
    while (rows-- != 0)
    {
        s32 n = cols;

        while (n-- != 0)
        {
            if (*cur == 0)
            {
                *cur = a->nextTile;
                a->nextTile++;
            }
            *cur = (*cur & 0xFFF) | (a->palette << 12);
            cur++;
        }
        cur += 0x20 - cols;
    }
    {
        u32 n = a->nextTile - start;

        if (n != 0)
            ((void (*)(u32, u32, u32))gData_080BB8BC[0])(0, (a->win->charBlock << 14) + (pin = 0x06000000 + (start << 5)), n << 5);
    }
    cur = (u16 *)(0x06000000 + (win->screenBlock << 11));
    c = *str++;
    while (c != 0)
    {
        s32 adv = 5;

        if (c > 0x20)
        {
            s32 yy = y;
            s32 r = ht;
            u32 *glyph;

            c = gData_080BB748[c];
            glyph = TextLayerTileAddr(a->font, c);
            adv = glyphAdv;
            if (a->widths != NULL)
                adv -= a->widths[c];
            r--;
            if (ht != 0)
            {
                do
                {
                    s32 xx = x;
                    s32 n = wt - 1;

                    if (wt != 0)
                    {
                        u16 *row = (u16 *)((u8 *)cur + ((yy & ~7) << 3));

                        do
                        {
                            GlyphBlit2x2(row + (xx >> 3), charBase, glyph, xx, yy);
                            xx += 8;
                            glyph += 8;
                        } while (n-- != 0);
                    }
                    yy += 8;
                } while (r-- != 0);
            }
        }
        x += adv;
        if (x > 0xEF)
            break;
        c = *str++;
    }
    return x;
}

