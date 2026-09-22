#include "global.h"

// @ 0x080385dc
void sub_080385DC(u16 lo, u16 hi)
{
    u16 i = lo;

    if (i > hi)
        return;

    do
    {
        gUnk_030003CC->unk20 &= ~(1 << i);
        gUnk_030003CC->unk00[i] |= 0xFFFF;
        gUnk_030003CC->unk22[i] |= 0xFFFF;
        i++;
    } while (i <= hi);
}
