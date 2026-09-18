#include "global.h"

// @ 0x08066434
u8 sub_08066434(void)
{
    u32 tmp[2];

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x34;
    return *(u8 *)tmp[0];
}

