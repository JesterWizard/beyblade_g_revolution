#include "global.h"

// @ 0x080705dc
void sub_080705DC(struct Unk705DC *a, s32 b)
{
    u32 t;
    u32 v;
    u32 mask;

    t = b << 24;
    v = 0xFFF;
    v &= a->unk14;
    mask = 0xF0 << 20;
    mask &= t;
    mask >>= 12;
    a->unk14 = v | mask;
}

