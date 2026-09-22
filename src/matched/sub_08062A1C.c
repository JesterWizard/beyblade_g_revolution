#include "global.h"

// @ 0x08062a1c
void sub_08062A1C(u32 v)
{
    u32 tmp[2];
    u32 base;

    tmp[0] = (u32)gUnk_030007B0;
    base = tmp[0];
    tmp[0] = 0x114;
    tmp[0] = base + tmp[0];
    *(u32 *)tmp[0] = v;
}

