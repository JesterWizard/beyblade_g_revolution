#include "global.h"

// @ 0x08062a74
void sub_08062A74(u32 a, void *src)
{
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    void *r5;
    u32 r6;

    r5 = src;
    r0 = a;
    r0 <<= 24;
    r0 >>= 24;
    r6 = (u32)&gUnk_030008D0;
    r1 = *(u32 *)r6;
    if (r1 == 0)
        goto done;
    r4 = 0x0F;
    r4 &= r0;
    r1 += 0x40;
    r0 = 1;
    r0 <<= r4;
    r2 = *(u16 *)r1;
    r0 |= r2;
    *(u16 *)r1 = (u16)r0;
    r2 = 0x080BB8C0;
r1 = r4 << 5;
    r0 = 0x05000200;
    r1 += r0;
    r3 = *(u32 *)r2;
    r0 = (u32)r5;
    r2 = 0x20;
    _08073C4C((void *)r0, (void *)r1, r2, (void *)r3);
    r0 = *(u32 *)r6;
    r4 <<= 2;
    r0 += r4;
    *(void **)r0 = r5;
done:
    return;
}

