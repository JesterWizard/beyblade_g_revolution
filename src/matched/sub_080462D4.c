#include "global.h"

// @ 0x080462d4

void sub_080462D4(void)
{
    s32 i;
    const u32 *table;

    if (gMainWorkPtr->unk184C != 0 &&
        gMainWorkPtr->unk184D == 0)
    {
        i = 0;
        table = (const u32 *)0x080979E4;
        while (i <= 1)
        {
            if (gMainWorkPtr->unk16B0[i].unk00 != 0)
            {
                if (gMainWorkPtr->unk16B0[i].unk04 == 0)
                    _08073C44(
                        (void *)i,
                        (void *)table[gMainWorkPtr->unk16B0[i].unk08]);
                else
                    gMainWorkPtr->unk16B0[i].unk04--;
            }
            i++;
        }
    }
}

