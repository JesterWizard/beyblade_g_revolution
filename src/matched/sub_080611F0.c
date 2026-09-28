#include "global.h"

// @ 0x080611f0
void TextWindowClose(void)
{
    void *p;

    VramSlotsRelease();
    p = *(void **)gUnk_03000790;
    if (p != 0)
    {
        HeapFree(p);
        *(void **)gUnk_03000790 = 0;
    }
    gUnk_03000798 = 0;
}

