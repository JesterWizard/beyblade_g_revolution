#include "global.h"

// @ 0x08042b28
void *sub_08042B28(u32 i)
{
    u32 r2;
    u32 r0;
    u32 r1;
    u32 r4;

    r2 = i;
    r0 = 0x08091004;
r1 = r2 << 2;
    r4 = r1 + r0;
    r0 = *(u32 *)r4;
    if (r0 == 0)
    {
        r0 = 0x083A2CD0;
        r1 = r2;
        sub_08067B98((void *)r0, r1);
    }
    return *(void **)r4;
}

