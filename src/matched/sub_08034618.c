#include "global.h"

// @ 0x08034618

void sub_08034618(struct Unk346C0 *a)
{
    s32 value;
    s32 delta;
    s32 scaled;

    if (a->unk2BC != a->unk2B8)
    {
        value = a->unk2C0;
        delta = _080740B0(a->unk2B8 << 16, a->unk2F4 << 8);
        scaled = delta * 3;
        scaled = (scaled << 3) + delta;
        scaled <<= 10;
        value += scaled >> 16;
        if (sub_0802C62C(1) <= 1 && a->unk30C == 0)
        {
            value >>= 1;
            if (value > 0x31)
                value = 0x32;
        }
        if (value > 0x63)
        {
            value = 0x64;
            a->unk2C4 = 1;
        }
        else
        {
            a->unk2C4 = 0;
        }
        a->unk04->unk28->unk24 = value;
        a->unk2BC = a->unk2B8;
    }
}

