#include "global.h"

// @ 0x08060d28

void sub_08060D28(struct Unk0798 *a)
{
    void **fn;
    void *dst;
    u32 n;
    u32 tmp;

    if (a != 0)
    {
        fn = (void **)0x080BB8BC;
        tmp = a->unk5D;
        dst = (void *)((tmp << 14) + (0xC0u << 19));
        tmp = a->unk94;
        n = tmp << 5;
        _08073C4C((void *)0, dst, n, *fn);
    }
}

