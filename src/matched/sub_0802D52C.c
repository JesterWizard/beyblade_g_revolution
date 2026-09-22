#include "global.h"

// @ 0x0802d52c
void sub_0802D52C(u32 a, s32 b)
{
    struct Unk026C *w;

    if (b != 0)
    {
        w = gUnk_0300026C;
        if (w->unk00 == 0)
        {
            w->unk08->unk18 = (u16)a;
            w->unk08->unk08 = gMainWorkPtr->unk0424->unk08 + 0xFFFFF800;
            w->unk08->unk0C = gMainWorkPtr->unk0424->unk0C + 0xFFFFF800;
            TextEntrySetPaletteBank(w->unk08, 2);
        }
    }
    else
    {
        gUnk_0300026C->unk08->unk08 = 0xFFFFC000;
        gUnk_0300026C->unk08->unk0C = 0xFFFFC000;
    }

    gUnk_0300026C->unk00 = b;
}

