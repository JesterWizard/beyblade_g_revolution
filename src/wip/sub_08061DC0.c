/* match-compiler: old_agbcc */
#include "global.h"

void sub_08061DC0(u16 arg0, u16 arg1)
{
    s32 stride;
    s32 lo;

    stride = (gUnk_03000798->unk98 >> 3) << 5;
    lo = gUnk_03000798->unk5D << 0xE;
    _08073C4C((void *)(lo + arg0 * stride + 0x06000000), (void *)(lo + arg1 * stride + 0x06000000), stride, *(void **)0x080BB8C0);
}
