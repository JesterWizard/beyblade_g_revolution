#include "global.h"

// @ 0x08073184
void MemClear(u8 *a, u32 n)
{
    u32 i;

    if (a != 0 && n != 0)
    {
        i = 0;
        while (i < n)
        {
            a[i] = 0;
            i++;
        }
    }
}

