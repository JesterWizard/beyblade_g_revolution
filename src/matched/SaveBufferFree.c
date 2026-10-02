#include "global.h"

// @ 0x08045a84
void SaveBufferFree(struct Unk45A84 *a)
{
    if (a->unk08 != 0)
    {
        if (a->unk00 != 0)
            HeapFree(a->unk00);
    }
    a->unk08 = 0;
    a->unk00 = 0;
    a->unk04 = 0;
}

