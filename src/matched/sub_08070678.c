#include "global.h"

// @ 0x08070678
void BtlReleaseEntry(struct Unk7069C *a)
{
    struct Unk705CC *p;

    sub_080700CC(&a->unk14);
    p = a->unk2C;
    if (p != 0)
    {
        sub_080705D4(p);
        BtlObjListMoveToHead((struct BtlObj *)a->unk2C);
        a->unk2C = 0;
    }
}

