#include "global.h"

// @ 0x08045aa8
void SaveBufferCreate(struct Unk45A84 *a)
{
    if (a->unk08 != 0)
        SaveBufferFree(a);
    a->unk00 = HeapAlloc(0xFB << 5);
    if (a->unk00 != 0)
    {
        a->unk04 = *(void **)a->unk00;
        a->unk08 = 1;
        SaveDataWrite(a->unk04, 1);
    }
}

