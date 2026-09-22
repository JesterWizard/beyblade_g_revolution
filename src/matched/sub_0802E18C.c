#include "global.h"

// @ 0x0802e18c
void sub_0802E18C(struct Unk310F0b *a, struct Unk310F0b *b, s32 c)
{
    if (c <= 99)
    {
        a->unk18 = Div(c, 10);
        b->unk18 = DivRemainder(c, 10);
    }
}

