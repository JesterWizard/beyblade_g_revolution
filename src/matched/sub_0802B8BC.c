#include "global.h"

// @ 0x0802b8bc
#include "global.h"

// @ 0x0802b8bc
u16 sub_0802B8BC(s32 a)
{
    register s32 r0 asm("r0");
    register u8 *r1 asm("r1");

    r0 = a;
    r0 <<= 16;
    r1 = *(u8 **)gUnk_03000264;
    r0 >>= 14;
    r0 += (u32)r1;
    return *(u16 *)(r0 + 2);
}

