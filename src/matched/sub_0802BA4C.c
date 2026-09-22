#include "global.h"

// @ 0x0802ba4c
void BtlFreeUnk1694Obj(void)
{
    void *p;

    p = *(void **)gUnk_03000268;
    if (p != 0)
    {
        BtlObjFree(p);
        *(void **)gUnk_03000268 = 0;
    }
    gMainWorkPtr->unk1694 = 0;
}

