#include "global.h"

// @ 0x080408c4
s32 sub_080408C4(void)
{
    s8 buf[12];

    CollectionFindByGroupSlot(1, 1, (struct CollectionLookup *)buf);
    return GetBeybladeNameWithIndex(buf[0]);
}

