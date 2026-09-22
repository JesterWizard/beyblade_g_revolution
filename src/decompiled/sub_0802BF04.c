#include "global.h"

// @ 0x0802bf04
void sub_0802BF04(u16 a, u8 b)
{
    s32 i;
    s8 sa;
    s8 sb;
    u8 zero;
    struct Unk1694 *p;

    if (gMainWorkPtr->unk1694 == NULL)
        return;

    i = 0;
    sa = (s8)a;
    sb = (s8)b;
    zero = 0;
    for (; i <= 0x7F; i++)
    {
        p = gMainWorkPtr->unk1694 + i;
        if (p->unk00 != sa)
            continue;
        if (p->unk03 != sb)
            continue;

        p = gMainWorkPtr->unk1694 + i;
        p->unk00 |= 0xFF;
        p = gMainWorkPtr->unk1694 + i;
        p->unk03 |= 0xFF;
        p = gMainWorkPtr->unk1694 + i;
        p->unk02 = zero;
        p = gMainWorkPtr->unk1694 + i;
        p->unk01 = zero;
        return;
    }
}
