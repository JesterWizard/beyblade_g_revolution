#include "global.h"

void sub_08062B9C(u32 arg0, u32 arg1)
{
    u32 hi;
    u32 lo;
    u32 i;
    u32 tmp;
    struct Unk62A74 *slot;

    lo = arg0 & 0xF;
    hi = arg1 & 0xF;
    if (lo > hi)
    {
        tmp = lo;
        lo = hi;
        hi = tmp;
    }

    for (i = lo; i <= hi; i++)
    {
        slot = *(struct Unk62A74 **)gUnk_030008D0;
        slot->unk40 &= ~(1 << i);
        slot->unk00[i] = 0;
    }
}
