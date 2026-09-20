#include "global.h"

// @ 0x08069988
#include "global.h"

/* match-flags: -fprologue-bugfix */

void *sub_08069988(u8 a)
{
    register u32 r0;
    register u32 r1;

    r0 = a;
    r1 = r0;
    if (r0 == 1)
        goto case1;
    if ((s32)r0 > 1)
        goto high;
    if (r0 == 0)
        goto case0;
    goto done;
high:
    if (r1 == 2)
        goto case2;
    if (r1 == 3)
        goto case3;
    goto done;
case0:
    r0 = 0x04000008;
    goto done;
case1:
    r0 = 0x0400000A;
    goto done;
case2:
    r0 = 0x0400000C;
    goto done;
case3:
    r0 = 0x0400000E;
done:
    return (void *)r0;
}

