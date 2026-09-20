#include "global.h"

// @ 0x080475c4
/* match-flags: -fprologue-bugfix */

void sub_080475C4(void)
{
    struct Unk473F8 *src;

    src = gUnk_03000630;
    if (src != 0)
    {
        gMainWorkPtr->unk1798 = src->unk40;
        gMainWorkPtr->unk179C = src->unk44;
    }
}

