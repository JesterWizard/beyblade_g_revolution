#include "global.h"

// @ 0x0806306c
void sub_0806306C(void)
{
    void **slotA;
    void **slotB;
    void **slotC;
    void **slotD;
    void **cpuSet;
    void *srcA;
    u32 dst;
    u32 n;

    slotA = (void **)gUnk_030008DC;
    srcA = *slotA;
    if (srcA != 0)
    {
        slotB = (void **)gUnk_030008D8;
        if (*slotB != 0)
        {
            slotC = (void **)gUnk_030008E0;
            if (*slotC != 0)
            {
                slotD = (void **)gUnk_030008D4;
                if (*slotD != 0)
                {
                    cpuSet = (void **)0x080BB8C0;
                    dst = 0xA0;
                    dst <<= 19;
                    n = 0x80;
                    n <<= 2;
                    _08073C4C(srcA, (void *)dst, n, *cpuSet);
                    _08073C4C(*slotB, (void *)0x05000200, n, *cpuSet);
                    if (*slotC != 0)
                    {
                        sub_0806A434(*slotC);
                        *slotC = 0;
                    }
                    if (*slotD != 0)
                    {
                        sub_0806A434(*slotD);
                        *slotD = 0;
                    }
                    *slotA = 0;
                    *slotB = 0;
                }
            }
        }
    }
}

