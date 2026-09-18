#include "global.h"

// @ 0x080679c0
void sub_080679C0(void *src)
{
    void **cpuSet;
    void *dst;
    u32 n;

    cpuSet = (void **)0x080BB8C0;
    dst = (void *)0x05000200;
    n = 0x80;
    n <<= 2;
    _08073C4C(src, dst, n, *cpuSet);
}

