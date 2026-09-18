#include "global.h"

// @ 0x08063104
void sub_08063104(void)
{
    void **slotA;
    void **slotB;
    void **cpuSet;
    void *srcA;
    u32 dst;
    u32 n;

    slotA = (void **)gUnk_030008DC;
    srcA = *slotA;
    if (srcA != 0)
    {
        slotB = (void **)gUnk_030008E0;
        if (*slotB != 0)
        {
            cpuSet = (void **)0x080BB8C0;
            dst = 0xA0;
            dst <<= 19;
            n = 0x80;
            n <<= 2;
            _08073C4C(srcA, (void *)dst, n, *cpuSet);
            if (*slotB != 0)
            {
                sub_0806A434(*slotB);
                *slotB = 0;
            }
            *slotA = 0;
        }
    }
}

