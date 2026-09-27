#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08034420
void Unk346C0Init(struct Unk346C0 *out, struct Unk346C0Inner *a, struct Unk346C0Inner *b, u8 mode)
{
    out->unk04 = b;
    out->unk00 = a;
    out->unk19 = 0;
    out->unk18 = 0;
    out->unk2C5 = 0;
    out->unk2C8 = 0;
    out->unk2CC = 0;
    out->unk2D0 = 0;
    out->unk2B0 = 0;
    out->unk2B4 = 0;
    out->unk2E4 = 0x10000;
    out->unk2E8 = 0x10000;
    out->unk2EC = 0;
    out->unk2F0 = 0;
    out->unk2F4 = 0;
    out->unk2F8 = -1;
    out->unk30C = mode;
    out->unk300 = 0;
    out->unk302 = 0;
    out->unk304 = 0;
    out->unk30E = 1;
    out->unk30D = 0;
    out->unk30F = 0;
    out->unk310 = 0;
    out->unk311 = 0;
    out->unk312 = 0;
    out->unk313 = 0;
    out->unk314 = 0;
    out->unk2B8 = 0;
    out->unk2C4 = 0;
    out->unk2BC = 0;
    out->unk2C0 = b->unk28->unk24;
    DebugPrint((void *)0x0833C5AC, out->unk30C, b->unk28->unk24);
    if (out->unk00 != NULL)
    {
        if (out->unk00->unk00 != NULL)
            out->unk2D0 = out->unk00->unk00->unk14 >> 12;
        out->unk2DC = a->unk30;
        out->unk2D8 = a->unk4C;
        out->unk2D4 = a->unk48;
        out->unk2E0 = a->unk34;
    }
}

