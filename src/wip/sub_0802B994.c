#include "global.h"

void *sub_0802B994(void)
{
    u32 key = gMainWorkPtr->unk1690->unk00;
    struct Unk7709C *table = (struct Unk7709C *)0x0807709C;

    if (table->unk04 == 0)
        return NULL;

    for (;;)
    {
        if (table->unk00 == key)
            return (void *)table->unk04;
        table++;
        if (table->unk04 == 0)
            return NULL;
    }
}
