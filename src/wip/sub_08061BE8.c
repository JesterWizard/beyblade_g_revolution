#include "global.h"

void sub_08061BE8(void)
{
    s32 n;
    struct Unk0770 *entry;
    struct Unk0798 *p;
    register void **handler_slot asm("r6");
    s32 lo;

    n = (s32)gUnk_03000794 - 1;
    if (n < 0)
        return;

    entry = gUnk_03000770 + n;
    handler_slot = (void **)entry->unk00;
    if (handler_slot == 0)
        return;

    p = gUnk_03000798;
    lo = (p->unk5D << 0xE) + 0x06000000;
    _08073C4C(*handler_slot, (void *)lo, p->unk94 << 5, *(void **)0x080BB8C0);

    p->unk90 = entry->unk04;
    p->unk92 = entry->unk06;
}
