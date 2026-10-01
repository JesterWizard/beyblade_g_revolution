#include "global.h"

// @ 0x0802c5dc
s32 BtlUnk1694FindAndMark(s8 a)
{
    s32 i;
    s8 val;

    val = (s8)a;
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].group == val)
            {
                gMainWorkPtr->unk1694[i].slot = 1;
                return 1;
            }
        }
    }
    return 0;
}

