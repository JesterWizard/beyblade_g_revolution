#include "global.h"

// @ 0x08042B28
void *sub_08042B28(u32 i)
{
    register u32 index asm("r2");
    void **entry;

    index = i;
    entry = (void **)0x08091004 + index;
    if (*entry == 0)
        sub_08067B98((void *)0x083A2CD0, index);
    return *entry;
}
