#include "global.h"

// @ 0x080405e8
void sub_080405E8(void *a)
{
    struct Unk047C *p;
    u32 n;

    p = gUnk_0300047C;
    n = p->unk80C;
    if ((s32)n <= 0x1FE)
    {
        p->unk00[n] = a;
        p->unk80C = n + 1;
    }
}

