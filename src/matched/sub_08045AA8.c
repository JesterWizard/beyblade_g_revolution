#include "global.h"

// @ 0x08045aa8
void sub_08045AA8(struct Unk45A84 *a)
{
    if (a->unk08 != 0)
        sub_08045A84(a);
    a->unk00 = BtlObjAlloc(0xFB << 5);
    if (a->unk00 != 0)
    {
        a->unk04 = *(void **)a->unk00;
        a->unk08 = 1;
        sub_08045198(a->unk04, 1);
    }
}

