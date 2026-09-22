#include "global.h"

// @ 0x08031300
void sub_08031300(struct Unk312EC *a)
{
    s32 t;
    struct Unk705DC *p;
    u32 v;

    if (a->unk08 == 0)
        return;
    if (a->unk04 < 0)
    {
        sub_080312D8(a);
        return;
    }
    t = a->unk04 - 1;
    a->unk04 = t;
    p = a->unk0C;
    if (p == 0)
        return;
    v = p->unk14 >> 12;
    if ((t & 5) != 0)
        return;
    if (v == (s32)a->unk01)
        TextEntrySetPaletteBank(p, (u8)a->unk00);
    else
        TextEntrySetPaletteBank(p, (u8)a->unk01);
}
