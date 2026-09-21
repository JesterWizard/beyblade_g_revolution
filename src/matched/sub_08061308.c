#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061308
/* match-compiler: old_agbcc */
void sub_08061308(void)
{
    struct Unk0798 *s;
    void **fn;
    void *dst;
    u32 n;
    u16 tmp;

    fn = (void **)0x080BB8BC;
    s = gUnk_03000798;
    tmp = s->unk5D;
    dst = (void *)((tmp << 14) + (0xC0u << 19));
    tmp = s->unk94;
    n = tmp << 5;
    _08073C4C((void *)0, dst, n, *fn);
}

