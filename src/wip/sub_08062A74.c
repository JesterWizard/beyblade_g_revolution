#include "global.h"

void sub_08062A74(u8 arg0, void *arg1)
{
    struct Unk62A74 *slot;
    u32 idx;

    slot = *(struct Unk62A74 **)gUnk_030008D0;
    if (slot == 0)
        return;

    idx = arg0 & 0xF;
    slot->unk40 |= 1 << idx;
    _08073C4C(arg1, (void *)(0x05000200 + (idx << 5)), 0x20, *(void **)0x080BB8C0);
    (*(struct Unk62A74 **)gUnk_030008D0)->unk00[idx] = arg1;
}
