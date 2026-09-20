#include "global.h"

// @ 0x0803DCFC
void *sub_0803DCFC(u32 i)
{
    u32 index;
    u32 offset;

    index = i;
    if (index <= 0x52)
        goto valid;
    sub_08067B98((void *)0x0833D1E0, (void *)0x0833D1F4);
    return 0;
valid:
    offset = index << 2;
    offset += index;
    offset <<= 3;
    return (void *)(0x0807A1F4 + offset);
}
