#include "global.h"

// @ 0x0803dbd0
#include "global.h"

/* match-flags: -fprologue-bugfix */

u32 sub_0803DBD0(u32 a)
{
    register s32 r3 asm("r3");
    register u32 r2 asm("r2");
    register u32 r1 asm("r1");
    register u32 r0 asm("r0");

    r3 = a;
    if (r3 >= 0)
    {
        r2 = 0x080796DC;
        asm("" : "+r"(r2), "+r"(r3));
        r0 = gMainWorkPtr->unk1818;
        r1 = r0 << 2;
        r0 = r3 << 2;
        r0 = r0 + r3;
        r0 <<= 3;
        r1 = r1 + r0;
        r1 = r1 + r2;
        r0 = *(u32 *)r1;
        goto done;
    }
    r1 = 0x08097458;
    asm("" : "+r"(r1));
    r0 = gMainWorkPtr->unk1818;
    r0 <<= 2;
    r0 = r0 + r1;
    r0 = *(u32 *)r0;
done:
    return r0;
}

