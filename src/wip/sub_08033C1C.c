#include "global.h"

// @ 0x08033c1c
void sub_08033C1C(void)
{
    register struct Unk0380 *r1;
    u32 tmp[1];

    tmp[0] = gUnk_03000380;
    r1 = (struct Unk0380 *)tmp[0];
    if (r1->unk09 == 1)
    {
        r1->unk09 = 0;
        r1->unk0A = 0;
        sub_080358CC(&r1->unk0C);
    }
}
