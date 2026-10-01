#include "global.h"

// @ 0x08047594

void SparklesHide(void)
{
    s32 i;
    struct Unk474ACSlot *slot;

    if (gData_03000630 != 0)
    {
        for (i = 0; i < 16; i++)
        {
            slot = gData_03000630->unk00[i];
            slot->unk08 = -0x4000;
            slot->unk0C = -0x4000;
        }
    }
}
