#include "global.h"

// @ 0x08062634
/* match-flags: -fprologue-bugfix */

void sub_08062634(struct Unk62634 *a, u32 b, u32 c, u32 d)
{
    if (a != 0)
    {
        a->unk1C = b;
        a->unk20 = c;
        a->unk18 = d;
    }
}

