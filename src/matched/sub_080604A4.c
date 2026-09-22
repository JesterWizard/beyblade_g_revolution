#include "global.h"

// @ 0x080604a4
void sub_080604A4(void)
{
    void *p;

    p = *(void **)gUnk_0300075C;
    if (p != 0)
    {
        BtlObjFree(p);
        *(void **)gUnk_0300075C = 0;
        *(void **)gUnk_03000750 = 0;
    }
}

