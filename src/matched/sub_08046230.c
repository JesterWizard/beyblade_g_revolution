#include "global.h"

// @ 0x08046230
void BtlResetUnk16B0(s32 a)
{
    if ((u32)a > 1)
        return;

    if (gMainWorkPtr->unk16B0[a].unk00 == 1)
    {
        gMainWorkPtr->unk16B0[a].unk00 = 0;
        gMainWorkPtr->unk16B0[a].unk04 = -1;
        gMainWorkPtr->unk16B0[a].unk08 = -1;
    }
}

