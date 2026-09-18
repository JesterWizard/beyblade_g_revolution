#include "global.h"

// @ 0x080686b4
void sub_080686B4(struct Unk68574 *a, u32 *b)
{
    if (a->unkB0 != 0)
        _08073C4C(a, b, (u32)a, a->unkB0);
    else
    {
        b[0] = a->unk04;
        b[1] = a->unk08;
        b[2] = a->unk0C;
    }
}

