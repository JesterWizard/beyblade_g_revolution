#include "global.h"

// @ 0x080405e8
void sub_080405E8(void *a)
{
    struct MessageQueue *p;
    u32 n;

    p = gUnk_0300047C;
    n = p->writeIndex;
    if ((s32)n <= 0x1FE)
    {
        p->entries[n] = a;
        p->writeIndex = n + 1;
    }
}

