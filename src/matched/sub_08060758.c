#include "global.h"

// @ 0x08060758
void sub_08060758(void)
{
    void **slotA;
    void **slotB;
    void **fn;
    void *p;
    void *q;
    struct Unk0758 *r;

    slotA = (void **)gUnk_03000754;
    *slotA = 0;
    slotB = (void **)gUnk_03000758;
    *slotB = 0;
    p = sub_0806A3A4(0x0C);
    *slotA = p;
    if (p != 0)
    {
        q = *(void **)p;
        *slotB = q;
        fn = (void **)0x080BB8BC;
        _08073C4C((void *)0, q, 0x0C, *fn);
        r = *slotB;
        r->unk06 = 0;
    }
}

