#include "global.h"

// @ 0x08033958
/* match-flags: -fprologue-bugfix */

s32 sub_08033958(struct Unk33958 *a)
{
    s32 r2;
    s32 r1;
    s32 r0;

    r2 = 0;
    r1 = a->unk00;
    r0 = *a->unk04;
    if (r1 == r0)
        r2 = 1;
    r0 = r2;
    return r0;
}

