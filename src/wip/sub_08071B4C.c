#include "global.h"

// @ 0x08071b4c
void sub_08071B4C(void)
{
    register u32 r0;
    register u32 r1;
    register u32 r2;
    register u32 r3;
    register u32 r4;

    r0 = 0x04000084;
    r1 = 0;
    *(u16 *)r0 = (u16)r1;
    r0 -= 2;
    *(u16 *)r0 = (u16)r1;
    r0 += 0x42;
    r4 = 0;
    *(u32 *)r0 = r4;
    r0 += 0x0C;
    *(u32 *)r0 = r4;
    r0 += 0x34;
    *(u32 *)r0 = r4;
    r0 -= 4;
    *(u32 *)r0 = r4;

    r3 = 0x080BB8BC;
    r0 = gUnk_030040DC;
    r1 = *(u32 *)r0;
r0 = gUnk_0300410C;
r2 = *(u16 *)r0;
    r0 = r2 << 1;
    r0 += 0x20;
    r2 = r2 + r0;
    r3 = *(u32 *)r3;
    r0 = 0;
    _08073C4C((void *)r0, (void *)r1, r2, (void *)r3);

    r0 = gUnk_030000C0;
    *(s32 *)r0 = r4;
}

