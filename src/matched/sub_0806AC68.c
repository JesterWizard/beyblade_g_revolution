#include "global.h"

// @ 0x0806ac68
#include "global.h"

/* match-flags: -fprologue-bugfix */

u32 sub_0806AC68(u8 *s)
{
    register u32 r2;
    register u32 r1;
    register u8 *r0;

    r2 = 0;
    goto test;
loop:
    r0++;
    if (r1 != 0x20)
        r2++;
test:
    r1 = *r0;
    if (r1 != 0)
        goto loop;
    r0 = (u8 *)r2;
    return (u32)r0;
}

