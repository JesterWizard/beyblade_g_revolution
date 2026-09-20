#include "global.h"

// @ 0x0806def4
#include "global.h"

/* match-flags: -fprologue-bugfix */

s32 sub_0806DEF4(struct Unk6DEF4 *a, s32 b)
{
    register s32 r2;
    register s32 r0;
    register s32 r1;

    r2 = a->unk04;
    r0 = *a->unk00;
    r1 = b;
    if (r1 >= r0)
    {
        r0 = 0;
        goto done;
    }
    r0 = r1 << 4;
    r0 = r2 + r0;
done:
    return r0;
}

