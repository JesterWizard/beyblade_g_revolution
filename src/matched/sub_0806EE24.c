#include "global.h"

// @ 0x0806ee24
void sub_0806EE24(struct Unk6EE24 *a)
{
    u16 *io;

    io = (u16 *)(0x80 << 19);
    *io = a->unk358;
    a->unk356 = 0xFF;
    a->unk355 = 0xF;
}

