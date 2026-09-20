#include "global.h"

// @ 0x080674bc
u32 sub_080674BC(u32 a)
{
    register int v;
    register u32 r2;

    v = (u16)a;
    r2 = 0;
    if (v == 4)
        *((u32 *)0x030009B0) = 0x083A93C8;
    else if (v == 0x40)
        *((u32 *)0x030009B0) = 0x083A93D4;
    else
    {
        *((u32 *)0x030009B0) = 0x083A93C8;
        r2 = 1;
    }
    return r2;
}

