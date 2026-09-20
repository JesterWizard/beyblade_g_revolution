#include "global.h"

void sub_08059DC8(u32 arg0, void *list)
{
    u32 a = 1;
    u32 c = 0;
    u32 b = 0;
    register void **table asm("r5");
    register void *handler asm("r4");

    if (list == 0)
        return;

    *(u32 *)gUnk_03000734 = arg0;
    table = (void **)0x08099710;
    do
    {
        handler = table[*(u32 *)list];
        list = (void *)_08073C50(list, &a, &b, &c);
    } while (c != 0);
}
