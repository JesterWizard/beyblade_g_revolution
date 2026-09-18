#include "global.h"

// @ 0x0803dd60
u32 sub_0803DD60(u32 a)
{
    register u32 r2 asm("r2") = 0x0807B0C4;
    register u32 r1 asm("r1");
    register u32 r3 asm("r3");
    register u32 r0 asm("r0") = a;

    asm("" : "+r"(r2));
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
