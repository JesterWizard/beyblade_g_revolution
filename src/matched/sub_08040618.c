#include "global.h"

// @ 0x08040618
s32 sub_08040618(void)
{
    struct Unk047C *p;
    u32 n;
    s32 v;

    p = gUnk_0300047C;
    n = p->unk808;
    v = (s32)p->unk00[n];
    p->unk808 = n + 1;
    if (v >= 0)
        return GetPlayerKeyedWord((void *)v);
    return 0;
}

