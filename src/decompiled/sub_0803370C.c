#include "global.h"

s32 sub_0803139C(
    void *a, s32 b, s32 c, void *d, u32 e);
void sub_08031368(void *a, u32 b, s32 *c, s32 *d);

void sub_0803370C(void)
{
    struct Unk67BB8 *entry;
    s32 count;
    s32 position;
    s32 i;
    s32 value_a;
    s32 value_b;

    if (gBattleWork->unk0B6C != 1)
        return;
    gBattleWork->unk0B78--;
    if (gBattleWork->unk0B78 < 0)
    {
        sub_08033878();
        return;
    }
    if (gBattleWork->unk0B64 < gBattleWork->unk0B68)
    {
        gBattleWork->unk0B64 += 4;
        if (gBattleWork->unk0B64 > gBattleWork->unk0B68)
            gBattleWork->unk0B64 = gBattleWork->unk0B68;
    }
    count = sub_0803139C(
        gBattleWork->unk0B54, gBattleWork->unk0B64, 4,
        (void *)0x0810B4E0, 1);
    position = gBattleWork->unk0B7C + (count - 1) * 0x700;
    for (i = 0; i < count; i++)
    {
        entry = (struct Unk67BB8 *)gBattleWork->unk0B54[i];
        if (entry != 0)
        {
            entry->unk08 = position;
            entry->unk0C = gBattleWork->unk0B74;
        }
        position -= 0x700;
    }
    gBattleWork->unk0B74 +=
        (gBattleWork->unkBB0 - gBattleWork->unk0B74) >> 3;
    if (gBattleWork->unk0B78 == 1)
    {
        value_a = 0;
        value_b = 0;
        if (gBattleWork->unk0AE8.fields.unkB00 != 0)
            sub_08031368(
                gBattleWork->unk0AE8.fields.unkB00, 8,
                &value_a, &value_b);
        gBattleWork->unk0B7C +=
            (value_a - gBattleWork->unk0B7C) >> 3;
    }
    else
    {
        value_a = 0;
        value_b = 0;
        if (gBattleWork->unk0AE8.fields.unkB20 != 0)
            sub_08031368(
                gBattleWork->unk0AE8.fields.unkB20, 8,
                &value_a, &value_b);
        gBattleWork->unk0B7C +=
            (value_a - gBattleWork->unk0B7C) >> 3;
    }
}
