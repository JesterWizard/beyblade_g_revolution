#include "global.h"

// @ 0x08061bdc
/* match-flags: -fprologue-bugfix */

void sub_08061BDC(struct Unk61BDC *a)
{
    struct Unk61BDC *r1;
    u32 r0;

    r1 = a;
    if (r1 != 0)
    {
        r0 = 1;
        r1->unk14 = r0;
    }
}

