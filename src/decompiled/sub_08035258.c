#include "global.h"

void sub_08035258(struct Unk35258 *a, u32 b)
{
    u8 type;

    type = b;
    if (type == 1)
    {
        if ((a->unk2C5 & 2) == 0)
            return;
        sub_08038638(a->unkF8.unk3A >> 1);
        sub_08068808(&a->unkF8);
        a->unk2C5 &= 0xFD;
    }
    else if (type > 1)
    {
        if (type == 2)
        {
            if ((a->unk2C5 & 4) == 0)
                return;
            sub_08038638(a->unk1D4.unk3A >> 1);
            sub_08068808(&a->unk1D4);
            a->unk2C5 &= 0xFB;
        }
    }
    else if (type == 0)
    {
        if ((a->unk2C5 & 1) == 0)
            return;
        sub_08038638(a->unk1C.unk3A >> 1);
        sub_08068808(&a->unk1C);
        a->unk2B0 = type;
        a->unk2B4 = type;
        a->unk2C5 &= 0xFE;
    }
}
