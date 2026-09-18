#include "global.h"

// @ 0x08033a5c
void sub_08033A5C(struct Unk33A5C *a)
{
    u32 z;

    if (a->unk00 == 1)
    {
        z = 0;
        a->unk00 = z;
        sub_08034A68(a->unk04, (u32)a->unk08);
        sub_08034A68(a->unk08, (u32)a->unk04);
        sub_08035020(a->unk08, 0x2D);
        a->unk04 = (struct Unk346C0 *)z;
        a->unk08 = (struct Unk346C0 *)z;
        sub_080330F4(-0x80);
    }
}

