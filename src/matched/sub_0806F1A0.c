#include "global.h"

// @ 0x0806f1a0

s32 Unk84FindIndexByKey(struct Unk6F1A0 *a, u16 key, s16 n)
{
    s16 i;

    for (i = 0; i < n; i++)
    {
        if (key == a->unk00)
            return i;
        a++;
    }
    return -1;
}

