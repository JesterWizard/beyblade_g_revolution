#include "global.h"

// @ 0x08062238
void sub_08062238(struct Unk62634 *a)
{
    if (a != 0)
    {
        if (a->unk08 != 0)
        {
            sub_0806FE84(a->unk08);
            a->unk08 = 0;
        }
        sub_08062684(a);
    }
}

