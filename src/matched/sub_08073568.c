#include "global.h"

// @ 0x08073568

u8 sub_08073568(void **out, u8 count, u32 size)
{
    u32 i;
    void **p;

    if (out == 0 || size == 0)
        return 0;

    i = 0;
    if (i < count)
    {
        p = out;
        do
        {
            *p = BtlObjTableAdd(size);
            if (*p == 0)
            {
                DebugPrint((void *)0x083D26C0);
                return i;
            }
            p++;
            i++;
        } while (i < count);
    }

    return i;
}

