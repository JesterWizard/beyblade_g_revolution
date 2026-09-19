#include "global.h"

// @ 0x08035d1c
#include "global.h"

// @ 0x08035d1c
s32 sub_08035D1C(struct Unk346C0Inner *a, s32 b, s32 c)
{
    s32 v18;
    s32 v1C;
    s32 d0;
    s32 d1;

    if (a->unk14 > 0)
    {
        if (a->unk14 + a->unk20 < 0)
            return 1;
    }
    else if (a->unk20 <= 0)
    {
        a->unk14 = 0;
        a->unk20 = 0;

        v18 = a->unk18 + a->unk3C;
        v1C = a->unk1C + a->unk40;
        d0 = b - a->unk0C;
        d1 = c - a->unk10;
        d0 >>= 0xB;
        v18 += d0;
        a->unk18 = v18;
        d1 >>= 0xB;
        v1C += d1;
        a->unk1C = v1C;
    }

    return 0;
}

