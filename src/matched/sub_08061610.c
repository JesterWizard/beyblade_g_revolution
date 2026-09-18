#include "global.h"

// @ 0x08061610
void sub_08061610(u16 a)
{
    s32 v;
    struct Unk0798 *p;

    v = a;
    p = gUnk_03000798;
    v &= 15;
    v <<= 12;
    p->unk96 = v;
}

