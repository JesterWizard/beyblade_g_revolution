#include "global.h"

// @ 0x08068808
void sub_08068808(struct Unk68574 *a)
{
    if (a->unkB8 != 0)
    {
        sub_0806FE84(a->unkB8);
        a->unkB8 = 0;
    }
    if (a->unk7C != 0)
        BtlObjFree(a->unk7C);
    a->unk74 = -1;
    a->unk78 = 0;
    a->unk7C = 0;
}

