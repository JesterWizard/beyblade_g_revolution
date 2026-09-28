#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08053690
// Redraws the three visible rows of a list (empty list: a single message),
// highlighting the selected row and showing its cursor and item sprites.
void sub_08053690(void *arg)
{
    struct Unk65560 *a = arg;
    s32 i;
    u8 *label;

    TextGetAreaWidth();
    if (gData_030006F0 == 0)
    {
        u8 **strings;

        TextSetCursor(0, 0x38);
        strings = (u8 **)gData_08097458;
        TextDrawAlign(strings[gData_03000198->unk1818], 0x14, 2);
        return;
    }
    if (a->unk274[1] != NULL)
    {
        BtlObjPoolFree(a->unk274[1]);
        a->unk274[1] = NULL;
    }
    if (a->unk274[15] != NULL)
    {
        BtlObjPoolFree(a->unk274[15]);
        a->unk274[15] = NULL;
    }
    for (i = 0; i < 3; i++)
    {
        if (gData_030006E8[gData_030006EC + i].unk0C < 0)
            continue;
        TextSetCursor(0, i * 16 + 0x38);
        label = (u8 *)_080563A8(gData_030006E8[gData_030006EC + i].unk0D, gData_030006E8[gData_030006EC + i].unk0C);
        if (label != NULL)
            TextDrawAlign(label, 0x14, 2);
        else
            TextDrawAlign(gData_030006E8[gData_030006EC + i].unk04, 0x14, 2);
        if (i == gData_030006E4)
        {
            a->unk274[15] = BtlObjPoolAlloc(0);
            SpriteInitFromTemplate(a->unk274[15], (struct Unk6FF58Src *)0x0811FD5C, 0x800, 0x1000, 0, 0, 0, 0);
            a->unk274[15]->unk18 = (s8)gData_03000198->unk1694[gData_030006E8[gData_030006EC + i].unk0E].unk02 >> 2;
            if (a->unk274[1] != NULL)
            {
                BtlObjPoolFree(a->unk274[1]);
                a->unk274[1] = NULL;
            }
            a->unk274[1] = BtlObjPoolAlloc(0);
            SpriteInitFromTemplate(a->unk274[1], gData_030006E8[gData_030006EC + i].unk08, 0xBC00, 0x2000, 0, 0, 0, 0);
            TextRowSetPaletteBank((u16)(i * 2 + 11), 0xE, 3, 0x1A);
            TextRowSetPaletteBank((u16)(i * 2 + 12), 0xE, 3, 0x1A);
        }
        else
        {
            TextRowSetPaletteBank((u16)(i * 2 + 11), 0xF, 3, 0x1A);
            TextRowSetPaletteBank((u16)(i * 2 + 12), 0xF, 3, 0x1A);
        }
    }
}

