#include "global.h"

// @ 0x08070678
void BtlReleaseEntry(struct Unk7069C *a)
{
    struct Unk70354Object *p;

    BtlObjPoolReleaseChain(&a->unk14);
    p = a->unk2C;
    if (p != 0)
    {
        AffineObjUnlock(p);
        BtlObjListMoveToHead((struct BtlObj *)a->unk2C);
        a->unk2C = 0;
    }
}

