#include "global.h"

// @ 0x080475c4
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_080475C4(void)
{
    register struct Unk473F8 *r3 asm("r3");
    register u32 r1 asm("r1");
    register u32 r0 asm("r0");
    register u32 r2 asm("r2");

    r3 = gUnk_03000630;
    if (r3 != 0)
    {
        r1 = (u32)gMainWorkPtr;
        r0 = 0x1798;
        r2 = r1 + r0;
        r0 = r3->unk40;
        *(s32 *)r2 = r0;
        r0 = 0x179C;
        r1 = r1 + r0;
        r0 = r3->unk44;
        *(s32 *)r1 = r0;
    }
}

