#include "global.h"

// @ 0x08060468
void sub_08060468(void)
{
    void **slotA;
    void **slotB;
    void **fn;
    void *p;
    void *q;

    slotA = (void **)gUnk_03000750;
    *slotA = 0;
    slotB = (void **)gUnk_0300075C;
    *slotB = 0;
    p = BtlObjAlloc(0x18);
    *slotB = p;
    if (p != 0)
    {
        q = *(void **)p;
        *slotA = q;
        fn = (void **)0x080BB8BC;
        _08073C4C((void *)0, q, 0x18, *fn);
    }
}

