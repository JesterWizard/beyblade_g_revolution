#include "global.h"

// @ 0x08061e40
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_08061E40(struct Unk61E40 *a)
{
    struct Unk61E40 *r2;
    u32 r1;
    u32 r0;

    r2 = a;
    if (r2 != 0)
    {
        r1 = 0;
        r0 = 0;
        *(u16 *)&r2->unk10 = r0;
        *(u16 *)&r2->unk0A = r0;
        r2->unk15 = r1;
        r2->unk04 = r0;
    }
}

