#include "global.h"

// @ 0x08045c5c
u32 sub_08045C5C(u32 a, u32 b)
{
    vu16 *mask;

    mask = (vu16 *)gBtlInputMask;
    if (mask[0] == 0xFC00)
    {
        gMainWorkPtr->unk1778 = 0;
        gMainWorkPtr->unk1774 = 0;
        return 0;
    }
    if (gMainWorkPtr->unk1778 != 0)
    {
        gMainWorkPtr->unk1778 = gMainWorkPtr->unk1778 - 1;
        return 0;
    }
    if (gMainWorkPtr->unk1774 == mask[0])
        gMainWorkPtr->unk1778 = b;
    else
        gMainWorkPtr->unk1778 = a;
    gMainWorkPtr->unk1774 = mask[0];
    return mask[0];
}