#include "global.h"

// @ 0x0802c5dc
s32 BtlUnk1694FindAndMark(u8 a)
{
    s32 i;
    s8 val;

    val = (s8)a;
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if (gMainWorkPtr->unk1694[i].unk03 == val)
            {
                gMainWorkPtr->unk1694[i].unk01 = 1;
                return 1;
            }
        }
    }
    return 0;
}

