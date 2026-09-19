#include "global.h"

// @ 0x08073440
s32 sub_08073440(void *a, void *b)
{
    u8 *pa = a;
    u8 *pb = b;
    s32 i = 0;
    bool8 done = FALSE;

    if (a == 0 || b == 0)
        return -2;

    while (!done)
    {
        if (pa[i] > pb[i])
            return 1;
        if (pa[i] < pb[i])
            return -1;
        if (pa[i] == 0 && pb[i] == 0)
            done = TRUE;
        i++;
    }

    return 0;
}

