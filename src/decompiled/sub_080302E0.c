#include "global.h"

void sub_080302E0(struct Unk346C0 *a)
{
    s32 delta;
    s32 value;
    s32 offset;

    value = gBattleWork->unk13C[a->unk30C];
    offset = gBattleWork->unkAE8[a->unk30C];
    delta = _080740B0(value << 16, 0x900);
    if (a->unk04->unk28->unk1F & 0x40)
        offset -= delta;
    else
        offset += delta;
    gBattleWork->unkAE8[a->unk30C] = offset;
    offset >>= 8;
    offset &= 0xFF;
    if (a->unk00->unk00 != 0)
    {
        if ((delta >> 8) > 0x1F)
            a->unk00->unk00->unk18 = RandRange(2);
        else
            a->unk00->unk00->unk18 = 2;
        if (a->unk00->unk00->unk30 != 0)
            sub_08070354(
                a->unk00->unk00->unk30,
                a->unk00->unk00->unk14,
                a->unk00->unk00->unk16,
                offset);
    }
}
