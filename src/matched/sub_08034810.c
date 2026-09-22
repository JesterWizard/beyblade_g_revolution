#include "global.h"

// @ 0x08034810
void sub_08034810(struct Unk346C0 *a, u32 b)
{
    struct Unk346C0Inner *inner;
    u32 id;

    inner = a->unk00;
    if (inner != 0)
    {
        id = inner->unk00->unk14 >> 0xC;
        if ((b & 5) == 0)
        {
            if (id == a->unk2D0)
                id = 0xF;
            else
                id = a->unk2D0;
            TextEntrySetPaletteBank(a->unk00->unk00, (u8)id);
        }
    }
}

