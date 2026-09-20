#include "global.h"

// @ 0x080475f4
/* match-flags: -fprologue-bugfix */

void sub_080475F4(void)
{
    struct Unk473F8 *dst;

    dst = gUnk_03000630;
    if (dst != 0)
    {
        dst->unk40 = gMainWorkPtr->unk1798;
        dst->unk44 = gMainWorkPtr->unk179C;
    }
}

