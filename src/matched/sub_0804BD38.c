#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

// @ 0x0804bd38
// Redraw the five visible rows of the scrolling menu: label text, highlight
// the cursor row, and rebuild each row's icon sprite plus its palette.
void sub_0804BD38(void *arg)
{
    struct Unk4BD38 *a = arg;
    s16 *top = (s16 *)&gData_03000674;
    struct Unk4BD38Label *labels = gData_08098004;
    s32 i;
    u16 *pal;
    s32 y;

    i = 0;
    pal = (u16 *)0x05000360;
    for (i = 0; i < 5; i++)
    {
        labels = gData_08098004;
        y = i * 16;
        TextSetCursor(0, y + 0x18);
        TextDrawAlign(labels[*top + i].unk00, 0x1C, 2);
        if (i == (s16)gData_03000678)
        {
            TextRowSetPaletteBank((u16)(2 * i + 7), 0x0E, 4, 0x17);
            TextRowSetPaletteBank((u16)((i + 4) * 2), 0x0E, 4, 0x17);
        }
        else
        {
            TextRowSetPaletteBank((u16)(2 * i + 7), 0x0F, 4, 0x17);
            TextRowSetPaletteBank((u16)((i + 4) * 2), 0x0F, 4, 0x17);
        }
        if (a->unk274[i] != NULL)
        {
            BtlObjPoolFree(a->unk274[i]);
            a->unk274[i] = NULL;
        }
        a->unk274[i] = BtlObjPoolAlloc(0);
        SpriteInitFromTemplate(a->unk274[i], gData_080984F0[*top + i], 0xC400, (i * 16 + 0x38) << 8, 0, 0, 0, 0);
        TextEntrySetPaletteBank(a->unk274[i], (u8)(i + 11));
        ((void (*)(void *, void *, u32))gData_080BB8C0[0])(gData_08098764[*top + i], pal, 0x20);
        pal += 0x10;
    }
}

