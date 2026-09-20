#include "global.h"

// @ 0x08042B50
void *sub_08042B50(u32 i)
{
    register void **base asm("r0");
    register u32 index asm("r2");
    void **entry;

    base = (void **)0x080910E8;
    entry = base;
    index = i;
    entry += index;
    if (*entry == 0)
        sub_08067B98((void *)0x083A2CD0, index);
    return *entry;
}
