#include "global.h"

// @ 0x080475f4
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_080475F4(void)
{
    register struct Unk473F8 *r2 asm("r2");
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    register u32 r3 asm("r3");

    r2 = gUnk_03000630;
    if (r2 != 0)
    {
        r0 = (u32)gMainWorkPtr;
        r3 = 0x1798;
        r1 = r0 + r3;
        r1 = *(u32 *)r1;
        r2->unk40 = r1;
        r1 = 0x179C;
        r0 = r0 + r1;
        r0 = *(u32 *)r0;
        r2->unk44 = r0;
    }
}

