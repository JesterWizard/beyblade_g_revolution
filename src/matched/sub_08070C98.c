#include "global.h"

// @ 0x08070c98
void sub_08070C98(struct Unk70C98 *a, s32 b, s32 c)
{
    a->unk00 += (b << 16) >> 8;
    a->unk04 += (c << 16) >> 8;
    sub_080706B0(a);
}

