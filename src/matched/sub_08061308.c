#include "global.h"

// @ 0x08061308
#include "global.h"

// @ 0x08061308
void sub_08061308(void)
{
    struct Unk0798 *s;
    void **fn;
    void *dst;
    u32 n;
    register u32 tmp asm("r0");

    fn = (void **)0x080BB8BC;
    s = gUnk_03000798;
    tmp = s->unk5D;
    dst = (void *)((tmp << 14) + (0xC0u << 19));
    n = (u32)s->unk94 << 5;
    _08073C4C((void *)0, dst, n, *fn);
}

