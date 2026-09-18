#include "global.h"

// @ 0x0802d8dc
void sub_0802D8DC(void)
{
    struct Unk026C *p;
    struct Unk310F0b *a;
    struct Unk310F0b *b;
    struct Unk42E78 *row;
    s8 t;

    _0802D9A8();
    p = gUnk_0300026C;
    if (p->unk0C != 0)
    {
        sub_0802E18C((struct Unk310F0b *)p->unk1C, (struct Unk310F0b *)p->unk20, gMainWorkPtr->unk0878);
        a = (struct Unk310F0b *)gUnk_0300026C->unk14;
        b = (struct Unk310F0b *)gUnk_0300026C->unk18;
        t = sub_0802E1EC();
        sub_0802E18C(a, b, t);
        if (gUnk_0300026C->unk24 != 0)
        {
            t = sub_0802E1B4(gMainWorkPtr->unk0874);
            gUnk_0300026C->unk24->unk18 = t;
        }
    }
    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        row = (struct Unk42E78 *)sub_08042E78(p->unk4E);
        p = gUnk_0300026C;
        sub_0802E18C((struct Unk310F0b *)p->unk38, (struct Unk310F0b *)p->unk3C, (s8)row->unk03);
        a = (struct Unk310F0b *)gUnk_0300026C->unk30;
        b = (struct Unk310F0b *)gUnk_0300026C->unk34;
        t = sub_0802E210();
        sub_0802E18C(a, b, t);
        if (gUnk_0300026C->unk40 != 0)
        {
            t = sub_0802E1B4(row->unk00);
            gUnk_0300026C->unk40->unk18 = t;
        }
    }
}

