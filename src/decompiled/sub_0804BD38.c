#define sub_0804BD38 sub_0804BD38_x
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"
#undef sub_0804BD38

// Redraw the five visible rows of the scrolling menu: label text, highlight
// the cursor row, and rebuild each row's icon sprite plus its palette.
void sub_0804BD38(struct Unk4BD38 *a)
{
    s32 i;
    s32 y;
    s32 spriteY;
    s32 row7;
    s32 row8;
    u16 *pal;
    void **copyFn;

    i = 0;
    pal = (u16 *)0x05000360;
    spriteY = 0x3800;
    row8 = 0x80000;
    row7 = 0x70000;
    y = i;
    do
    {
        TextSetCursor(0, y + 0x18);
        TextDrawAlign((&gData_08098004[0] + (gData_03000674_A + i))->unk00, 0x1C, 2);
        if (i == *(s16 *)&gData_03000678)
        {
            TextRowSetPaletteBank(row7 >> 16, 0x0E, 4, 0x17);
            TextRowSetPaletteBank(row8 >> 16, 0x0E, 4, 0x17);
        }
        else
        {
            TextRowSetPaletteBank(row7 >> 16, 0x0F, 4, 0x17);
            TextRowSetPaletteBank(row8 >> 16, 0x0F, 4, 0x17);
        }
        if (a->unk274[i] != NULL)
        {
            BtlObjPoolFree(a->unk274[i]);
            a->unk274[i] = NULL;
        }
        a->unk274[i] = BtlObjPoolAlloc(0);
        SpriteInitFromTemplate(a->unk274[i], gData_080984F0[gData_03000674_B + i], 0xC400, spriteY, 0, 0, 0, 0);
        TextEntrySetPaletteBank(a->unk274[i], (u8)(i + 11));
        copyFn = (void **)gData_080BB8C0;
        _08073C4C(gData_08098764[gData_03000674_B + i], pal, 0x20, *copyFn);
        pal += 0x10;
        spriteY += 0x1000;
        row8 += 0x20000;
        row7 += 0x20000;
        y += 16;
        i++;
    } while (i <= 4);
}
