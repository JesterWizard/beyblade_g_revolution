#include "global.h"

// @ 0x0802d52c
void sub_0802D52C(u32 a, s32 b)
{
    struct StatusHud *w;

    if (b != 0)
    {
        w = gUnk_0300026C;
        if (w->markerShown == 0)
        {
            w->marker->unk18 = (u16)a;
            w->marker->unk08 = gMainWorkPtr->unk0424->unk08 + 0xFFFFF800;
            w->marker->unk0C = gMainWorkPtr->unk0424->unk0C + 0xFFFFF800;
            TextEntrySetPaletteBank(w->marker, 2);
        }
    }
    else
    {
        gUnk_0300026C->marker->unk08 = 0xFFFFC000;
        gUnk_0300026C->marker->unk0C = 0xFFFFC000;
    }

    gUnk_0300026C->markerShown = b;
}

