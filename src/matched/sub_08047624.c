#include "global.h"

// @ 0x08047624
s32 sub_08047624(u32 mode_arg)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    register u32 r2 asm("r2");
    register u32 r3 asm("r3");
    register u32 r4 asm("r4");
    register u32 r5 asm("r5");

    r0 = mode_arg;
    r0 <<= 24;
    r1 = r0 >> 24;
    r4 = r1;
    r0 = (u32)gMainWorkPtrLoc;
    r2 = *(u32 *)r0;
    r3 = 0xDC;
    r3 <<= 2;
    r0 = r2 + r3;
    r0 = *(u32 *)r0;
    r3 = (u32)((s32)r0 >> 8);
    r5 = 0xDD;
    r5 <<= 2;
    r0 = r2 + r5;
    r0 = *(u32 *)r0;
    r0 = (u32)((s32)r0 >> 8);
    r2 = 0;
    if (r1 == 1)
        goto case1;
    if ((s32)r1 > 1)
        goto high;
    if (r1 == 0)
        goto case0;
    goto done;
high:
    if (r4 == 2)
        goto case2;
    if (r4 == 3)
        goto case3;
    goto done;
case0:
    r1 = r3 - 1;
    r0 = 7;
    r0 &= r1;
    if (r0 == 0)
        goto common;
    r3 = 7;
loop0:
    r1--;
    r2++;
    r0 = r1;
    r0 &= r3;
    if (r0 != 0)
        goto loop0;
    goto common;
case1:
    r1 = r3 + 1;
    r0 = 7;
    r0 &= r1;
    if (r0 == 0)
        goto common;
    r3 = 7;
loop1:
    r1++;
    r2++;
    r0 = r1;
    r0 &= r3;
    if (r0 != 0)
        goto loop1;
    goto common;
case2:
    r1 = r0 - 1;
    r0 = 7;
    r0 &= r1;
    if (r0 == 0)
        goto common;
    r3 = 7;
loop2:
    r1--;
    r2++;
    r0 = r1;
    r0 &= r3;
    if (r0 != 0)
        goto loop2;
common:
    r0 = r2;
    asm("" : "+r"(r0));
    goto done;
case3:
    r1 = r0 + 1;
    r0 = 7;
    r0 &= r1;
    if (r0 == 0)
        goto case3_done;
    r3 = 7;
loop3:
    r1++;
    r2++;
    r0 = r1;
    r0 &= r3;
    if (r0 != 0)
        goto loop3;
case3_done:
    r0 = r2;
done:
    return (s32)r0;
}

