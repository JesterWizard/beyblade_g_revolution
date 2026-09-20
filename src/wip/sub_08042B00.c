#include "global.h"

// @ 0x08042b00
u32 sub_08042B00(u32 a)
{
    register u32 r2 = 0x08090FF0;
    register u32 r1;
    register u32 r3;
    register u32 r0 = a;
r1 = 0x03000198;
    r1 = *(u32 *)r1;
    r3 = 0x1818;
    r1 = r1 + r3;
    r1 = *(u8 *)r1;
    r1 = r1 << 2;
    r1 = r1 + r2;
    r1 = *(u32 *)r1;
    r0 = r0 << 2;
    r0 = r0 + r1;
    return *(u32 *)r0;
}
