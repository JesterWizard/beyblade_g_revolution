/* match-compiler: old_agbcc */
#include "global.h"

void sub_08061800(u16 arg0)
{
    struct Unk0798 *p = gUnk_03000798;
    s32 lo;
    u16 h;
    s32 stride;

    if (arg0 >= (p->unk9A >> 3) - 1)
        return;

    lo = (s32)p->unk5D;
    lo <<= 0xE;
    h = p->unk98;
    stride = (h >> 3) << 5;
    _08073C4C((void *)0, (void *)(lo + arg0 * stride + 0x06000000), stride, *(void **)0x080BB8BC);
}
