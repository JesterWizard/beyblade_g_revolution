#include "global.h"

// @ 0x08033e3c
void sub_08033E3C(struct Unk33F30 *a)
{
    s32 v;

    v = a->unk2C - 1;
    a->unk2C = v;
    if (v <= 0)
    {
        sub_08033D90(a);
        a->unk2C = (s32)a->unk34.unk0C;
    }
}

