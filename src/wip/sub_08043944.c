#include "global.h"

// @ 0x08043944
void sub_08043944(bool8 skip, u8 idx, u8 flags)
{
    struct Unk0554 *p;

    if (!skip)
    {
        p = gUnk_03000554;
        flags |= p->unk08[idx];
        p->unk08[idx] = flags;
        p->unk02 = flags;
    }
}
