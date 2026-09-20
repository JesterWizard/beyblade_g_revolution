#include "global.h"

// @ 0x08043944
void sub_08043944(bool8 skip, u8 idx, u8 flags)
{
    struct Unk0554 *p;
    u8 val;

    if (!skip)
    {
        p = gUnk_03000554;
        val = flags;
        val |= p->unk08[idx];
        p->unk08[idx] = val;
        p->unk02 = val;
    }
}
