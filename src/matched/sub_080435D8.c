#include "global.h"

extern const u32 *const gUnk_08094BB4[];

// @ 0x080435d8
void sub_080435D8(void)
{
    *gUnk_03000558Loc = gUnk_08094BB4[gMainWorkPtr->unk17F7][gMainWorkPtr->unk17F6];

    if (gMainWorkPtr->unk17F7 == 0)
        gUnk_03000554->unk02 = gUnk_03000554->unk08[gMainWorkPtr->unk17F6];
}
