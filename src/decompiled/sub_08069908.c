#include "global.h"

// @ 0x08069908
#include "global.h"

/* match-flags: -fprologue-bugfix */

u16 *BgGetHofsReg(u8 a)
{
    u32 r0;
    u32 r1;

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
    r0 = 0x04000010;
    goto done;
case1:
    r0 = 0x04000014;
    goto done;
case2:
    r0 = 0x04000018;
    goto done;
case3:
    r0 = 0x0400001C;
done:
    return (u16 *)r0;
}

