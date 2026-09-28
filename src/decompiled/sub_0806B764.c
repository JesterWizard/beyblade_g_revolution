/* match-compiler: old_agbcc */
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

s32 sub_0806B724(const u8 *s, const u8 *kern, s32 spacing);

struct TlObj
{
    u8 filler_00[4];
    u8 unk04;
    u8 unk05;
    u8 filler_06[6];
    u8 unk0C;
};

struct TlWin
{
    u8 filler_00[0x5C];
    u8 screenBlock;
    u8 charBlock;
    u8 unk5E;
};

struct TextLayer
{
    struct TlWin *win;
    u8 *widths;
    struct TlObj *obj;
    u8 unk0C;
    u8 filler_0D;
    u16 unk0E;
};

s32 sub_0806B764(struct TextLayer *a, s32 x, s32 y, u8 *str, u32 alignArg)
{
    u8 align = alignArg;
    struct TlWin *win = a->win;
    struct TlObj *obj = a->obj;
    u16 *cur = (u16 *)(0x06000000 + (win->screenBlock << 11));
    u32 charBase = 0x06000000 + (win->charBlock << 14);
    u32 wt = obj->unk04 >> 3;
    u32 ht = obj->unk05 >> 3;
    u32 glyphAdv = obj->unk04;
    s32 strW;
    s32 rows;
    s32 cols;
    u16 start;
    u32 c;
    u16 *reg;

    reg = BgGetCntReg(win->unk5E);
    if ((*reg & 0x80) || !(obj->unk0C & 1))
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
    start = a->unk0E;
    while (rows-- != 0)
    {
        s32 n = cols;

        while (n-- != 0)
        {
            if (*cur == 0)
            {
                *cur = a->unk0E;
                a->unk0E++;
            }
            *cur = (*cur & 0xFFF) | (a->unk0C << 12);
            cur++;
        }
        cur += 0x20 - cols;
    }
    {
        u32 n = a->unk0E - start;

        if (n != 0)
            ((void (*)(u32, u32, u32))gData_080BB8BC[0])(0, (a->win->charBlock << 14) + (0x06000000 + (start << 5)), n << 5);
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
            glyph = sub_0806BB38((void *)a->obj, c);
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
