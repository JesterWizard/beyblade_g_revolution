#include "global.h"

// @ 0x08042b50
void *sub_08042B50(u32 i)
{
    u32 r2;
    u32 r0;
    u32 r1;
    u32 r4;

    r2 = i;
    r0 = 0x080910E8;
r1 = r2 << 2;
    r4 = r1 + r0;
    r0 = *(u32 *)r4;
    if (r0 == 0)
    {
        r0 = 0x083A2CD0;
        r1 = r2;
        DebugPrint((void *)r0, r1);
    }
    return *(void **)r4;
}

