#include "global.h"

// @ 0x08034fbc
u8 sub_08034FBC(struct Unk34FF8 *a)
{
    u8 v;

    if (a->unk18 != 0)
        v = sub_08035908(&a->unk08);
    else
        v = 0;
    return v;
}

