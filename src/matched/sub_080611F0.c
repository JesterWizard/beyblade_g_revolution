#include "global.h"

// @ 0x080611f0
void sub_080611F0(void)
{
    void *p;

    sub_08061BAC();
    p = *(void **)gUnk_03000790;
    if (p != 0)
    {
        BtlObjFree(p);
        *(void **)gUnk_03000790 = 0;
    }
    gUnk_03000798 = 0;
}

