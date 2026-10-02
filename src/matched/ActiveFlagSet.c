#include "global.h"

// @ 0x08066440
void sub_08066440(u8 v)
{
    u32 tmp[2];

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    *(u8 *)tmp[0] = v;
}

