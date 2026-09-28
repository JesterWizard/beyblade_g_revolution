#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08061ef8
/* match-compiler: old_agbcc */
// Lays `text` out as glyph sprites: wraps it into up to four lines, aligns
// each line with sub_08062068 (`align`) and places one sprite per glyph,
// advancing by 0x10 minus the glyph's entry in the width table.
void sub_08061EF8(struct Unk62044 *a, const u8 *text, u32 unused, s32 y, u32 paletteArg, u32 tileArg, u32 align)
{
    u8 *lines[4];
    u8 palette = paletteArg;
    u16 tile = tileArg;
    s32 count;
    s32 i;
    u8 *p;
    s32 x;
    u32 c;

    sub_0806209C(a);
    if (StringArrayAlloc((void **)lines, 4, 0x60) < 4)
    {
        StringArrayFree((void **)lines, 4);
        return;
    }
    count = SplitStringIntoStringArray((void **)lines, (u8 *)text, 4, (u32)a->unk04, a->unk1C, a->unk20, a->unk20 >> 2, 0x60);
    for (i = 0; i < count; i++)
    {
        p = lines[i];
        a->unk18 = TextMeasureWidth(p, a->unk04, a->unk20, a->unk20 >> 2);
        x = sub_08062068((struct Unk62068 *)a, a->unk18, align);
        if (i == 0)
        {
            a->unk10 = x << 8;
            a->unk14 = y << 8;
        }
        for (c = *p++; c != 0; c = *p++)
        {
            if (c == ' ')
            {
                x += a->unk20 >> 2;
            }
            else
            {
                a->unk0C[a->unk24] = BtlObjPoolAlloc(tile);
                if (a->unk0C[a->unk24] == NULL)
                    return;
                SpriteInitFromTemplate((struct Sprite *)a->unk0C[a->unk24], a->unk08, x << 8, y << 8, 0, 0, 0, gData_080BB748[c]);
                x = 0x10 - a->unk04[gData_080BB748[c]] + x;
                TextEntrySetPaletteBank((struct Sprite *)a->unk0C[a->unk24], palette);
                a->unk24++;
            }
        }
        y += a->unk22;
    }
    StringArrayFree((void **)lines, 4);
}

