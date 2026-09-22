#include "global.h"

// @ 0x0802ba4c
void sub_0802BA4C(void)
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

