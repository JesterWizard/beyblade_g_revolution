#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080593a4
void sub_080593A4(struct Unk593A4 *a)
{
    s32 i;
    s32 last;
    s32 count;

    for (i = 0; i <= 7; i++)
    {
        if (a->unk4C[i] != NULL)
        {
            BtlObjPoolFree(a->unk4C[i]);
            a->unk4C[i] = NULL;
        }
    }
    count = (a->unk00->unk08 >> 8) - ((a->unk30->unk08 + a->unkA4) >> 8);
    last = DivRemainder(count, 32);
    count >>= 5;
    if (last > 24)
        last = 24;
    for (i = 0; i <= count; i++)
    {
        if (i == 0)
        {
            a->unk4C[0] = BtlObjPoolAlloc(10);
            sub_0806FF58(a->unk4C[0], (void *)0x0810E628, a->unk30->unk08 + a->unkA4, a->unk00->unk0C, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->unk4C[0], 9);
            if (i < count)
                a->unk4C[0]->unk18 = 24;
        }
        else
        {
            a->unk4C[i] = BtlObjPoolAlloc(10);
            sub_0806FF58(a->unk4C[i], (void *)0x081178B0, a->unk30->unk08 + a->unkA4 + (i << 13), a->unk00->unk0C, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->unk4C[i], 9);
            if (i < count)
                a->unk4C[i]->unk18 = 24;
        }
    }
}


