#include "global.h"

// @ 0x080735b0
void sub_080735B0(void **a, u32 n)
{
    u32 i;

    n = (u8)n;
    if (a == 0)
        return;
    for (i = 0; i < n; i++)
    {
        if (a[i] != 0)
            BtlObjTableRemove(a[i]);
    }
}

