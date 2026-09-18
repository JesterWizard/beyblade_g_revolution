#include "global.h"

// @ 0x080679a4
void sub_080679A4(void *src)
{
    void **cpuSet;
    u32 dst;
    u32 n;

    cpuSet = (void **)0x080BB8C0;
    dst = 0xA0;
    dst <<= 19;
    n = 0x80;
    n <<= 2;
    _08073C4C(src, (void *)dst, n, *cpuSet);
}

