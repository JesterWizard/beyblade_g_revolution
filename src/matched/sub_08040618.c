#include "global.h"

// @ 0x08040618
s32 MessageQueuePopKeyedWord(void)
{
    struct MessageQueue *p;
    u32 n;
    s32 v;

    p = gUnk_0300047C;
    n = p->readIndex;
    v = (s32)p->entries[n];
    p->readIndex = n + 1;
    if (v >= 0)
        return GetPlayerKeyedWord((void *)v);
    return 0;
}

