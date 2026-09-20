#include "global.h"

// @ 0x080618a8

void sub_080618A8(struct Unk618A8 *a, void *b, u16 c, u16 d, u16 e, u16 f)
{
    if (a == 0)
        return;
    if (b == 0)
        return;
    a->unk00 = b;
    a->unk08 = c;
    a->unk10 = 0;
    a->unk12 = d;
    a->unk0C = e;
    a->unk0E = f;
    a->unk0A = 0;
    a->unk15 = 0;
    a->unk04 = 0;
    a->unk14 = 1;
}

