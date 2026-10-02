#include "global.h"

// @ 0x08070678
void BtlReleaseEntry(struct TextGroup *a)
{
    struct AffineObj *p;

    BtlObjPoolReleaseChain(&a->glyphs);
    p = a->affine;
    if (p != 0)
    {
        AffineObjUnlock(p);
        BtlObjListMoveToHead((struct BtlObj *)a->affine);
        a->affine = 0;
    }
}

