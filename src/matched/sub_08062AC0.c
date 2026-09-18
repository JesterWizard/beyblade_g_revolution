#include "global.h"

// @ 0x08062ac0
void sub_08062AC0(void)
{
    void *p;
    void **fn;
    void *dst;
    u32 n;

    p = *(void **)gUnk_030008D0;
    if (p != 0)
    {
        fn = (void **)0x080BB8BC;
        _08073C4C((void *)0, p, 0x44, *fn);
        dst = (void *)0x05000200;
        n = 0x80;
        n <<= 2;
        _08073C4C((void *)0, dst, n, *fn);
    }
}

