#include "global.h"

// @ 0x0803e440
s32 BtlCountLiveSlots(void)
{
    s32 count;
    s32 i;
    s8 *p;

    count = 0;
    i = 0;
    p = gMainWorkPtr->unk1861;
    while (i <= 0x52)
    {
        if (p[i] > 0)
            count++;
        i++;
    }
    return count;
}

