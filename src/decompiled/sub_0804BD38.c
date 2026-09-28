#define sub_0804BD38 sub_0804BD38_x
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"
#undef sub_0804BD38

typedef void (*CpuCopyFunc)(const void *, void *, u32);

void sub_0804BD38(struct Unk4BD38 *a)
{
    s32 i;
    u16 *pal;

    pal = (u16 *)0x05000360;
    for (i = 0; i < 5; i++)
    {
        TextSetCursor(0, i * 16 + 0x18);
        TextDrawAlign(gData_08098004[(s16)gData_03000674 + i].unk00, 0x1C, 2);
        if (i == (s16)gData_03000678)
        {
            TextRowSetPaletteBank((u16)(i * 2 + 7), 0x0E, 4, 0x17);
            TextRowSetPaletteBank((u16)(i * 2 + 8), 0x0E, 4, 0x17);
        }
        else
        {
            TextRowSetPaletteBank((u16)(i * 2 + 7), 0x0F, 4, 0x17);
            TextRowSetPaletteBank((u16)(i * 2 + 8), 0x0F, 4, 0x17);
        }
        if (a->unk274[i] != NULL)
        {
            BtlObjPoolFree(a->unk274[i]);
            a->unk274[i] = NULL;
        }
        a->unk274[i] = BtlObjPoolAlloc(0);
        SpriteInitFromTemplate(a->unk274[i], gData_080984F0[(s16)gData_03000674 + i], 0xC400, i * 0x1000 + 0x3800, 0, 0, 0, 0);
        TextEntrySetPaletteBank(a->unk274[i], (u8)(i + 11));
        ((CpuCopyFunc)gData_080BB8C0[0])(gData_08098764[(s16)gData_03000674 + i], pal, 0x20);
        pal += 0x10;
    }
}

