#include "global.h"

// @ 0x08047594

void SparklesHide(void)
{
    s32 i;
    struct SparkleSlot *slot;

    if (gData_03000630 != 0)
    {
        for (i = 0; i < 16; i++)
        {
            slot = gData_03000630->slots[i];
            slot->x = -0x4000;
            slot->y = -0x4000;
        }
    }
}
