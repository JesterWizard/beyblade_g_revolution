#include "global.h"

// @ 0x08060d28

void TextWindowClearTiles(struct TextWindow *a)
{
    void **fn;
    void *dst;
    u32 n;
    u32 tmp;

    if (a != 0)
    {
        fn = (void **)0x080BB8BC;
        tmp = a->charBlock;
        dst = (void *)((tmp << 14) + (0xC0u << 19));
        tmp = a->tileCount;
        n = tmp << 5;
        _08073C4C((void *)0, dst, n, *fn);
    }
}

