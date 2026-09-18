#include "global.h"

// @ 0x080611a4
void sub_080611A4(void)
{
    void **slotA;
    void **slotB;
    void **slotC;
    void **fn;
    void *p;
    void *q;

    slotA = (void **)gUnk_03000790;
    *slotA = 0;
    slotB = (void **)0x03000798;
    *slotB = 0;
    slotC = (void **)gUnk_03000794;
    *slotC = 0;
    p = sub_0806A3A4(0xAC);
    *slotA = p;
    if (p != 0)
    {
        q = *(void **)p;
        *slotB = q;
        fn = (void **)0x080BB8BC;
        _08073C4C((void *)0, q, 0xAC, *fn);
    }
    else
        sub_080611F0();
}

