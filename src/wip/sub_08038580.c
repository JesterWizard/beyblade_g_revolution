#include "global.h"

// @ 0x08038580
void sub_08038580(void *dst, u32 indexArg)
{
    u8 index;
    u8 original;

    index = indexArg;
    original = index;
    if (gUnk_030003CC == 0)
        return;
    if (((gUnk_030003CC->unk20 >> index) & 1) == 0)
    {
        _08073C4C(dst, (void *)(0x05000200 + (index << 5)), 0x20, *(void **)0x080BB8C0);
        gUnk_030003CC->unk20 |= 1 << index;
    }
    gUnk_030003CC->unk22[original]++;
}
