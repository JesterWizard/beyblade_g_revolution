#include "global.h"

// @ 0x0803e1f4
void *sub_0803E1F4(s16 a, s16 b)
{
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gMainWorkPtr->unk08D0[i].unk23 == b
            && gMainWorkPtr->unk08D0[i].unk1C == a
            && gMainWorkPtr->unk087C[i] == 1)
        {
            return &gMainWorkPtr->unk08D0[i];
        }
    }

    return 0;
}

