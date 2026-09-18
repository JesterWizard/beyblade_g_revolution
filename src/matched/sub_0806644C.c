#include "global.h"

// @ 0x0806644c
s8 sub_0806644C(void)
{
    u32 tmp[2];
    s32 val;

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    val = *(u8 *)tmp[0];
    val <<= 24;
    val >>= 24;
    return (s8)val;
}

