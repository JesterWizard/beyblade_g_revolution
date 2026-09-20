#include "global.h"

// @ 0x08038580
void sub_08038580(void *dst, u32 indexArg)
{
    struct Unk3CC *p;
    u8 index;
    u8 original;

    index = indexArg;
    original = index;
    p = gUnk_030003CC;
    if (p == 0)
        return;
    if (((p->unk20 >> index) & 1) == 0)
    {
        _08073C4C(dst, (void *)(0x05000200 + (index << 5)), 0x20, *(void **)0x080BB8C0);
        p = gUnk_030003CC;
        p->unk20 |= 1 << index;
    }
    p = gUnk_030003CC;
    p->unk22[original]++;
}
