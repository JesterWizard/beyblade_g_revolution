#include "global.h"

// @ 0x080615ec
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_080615EC(u32 x, u32 y)
{
    register u32 r2;
    register u32 r3;
    register struct Unk0798 *r0;
    register u16 *r1;

    r2 = x;
    r3 = y;
    if (r2 > 0xEF)
        r2 = 0;
    if (r3 > 0x9F)
        r3 = 0;
    r0 = gUnk_03000798;
    r1 = &r0->unk90;
    *r1 = r2;
    r0->unk92 = r3;
}

