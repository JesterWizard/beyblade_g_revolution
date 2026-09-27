#include "global.h"
#include "ram_map.h"

union DigitView { s32 words[4]; struct Unk705DC obj; };

s32 sub_0803139C(struct Unk705DC **array, s32 value, s32 count, void *table, u8 withPoint);
void sub_08031368(struct Unk705DC **objs, u32 n, s32 *x, s32 *y);

void sub_0803370C(void)
{
    s32 count;
    s32 x;
    s32 i;

    if (gBattleWork->unk0B6C != 1)
        return;
    if (--gBattleWork->unk0B78 >= 0)
    {
        if (gBattleWork->unk0B64 < gBattleWork->unk0B68)
        {
            gBattleWork->unk0B64 += 4;
            if (gBattleWork->unk0B64 > gBattleWork->unk0B68)
                gBattleWork->unk0B64 = gBattleWork->unk0B68;
        }
        count = sub_0803139C((struct Unk705DC **)gBattleWork->unk0B54, gBattleWork->unk0B64, 4, (void *)0x0810B4E0, 1);
        x = gBattleWork->unk0B7C + (count - 1) * 0x700;
        for (i = 0; i < count; i++)
        {
            union DigitView *digit = gBattleWork->unk0B54[i];

            if (digit != NULL)
            {
                digit->obj.unk08 = x;
                digit->obj.unk0C = gBattleWork->unk0B74;
            }
            x -= 0x700;
        }
        gBattleWork->unk0B74 += (gBattleWork->unk0B70 - gBattleWork->unk0B74) >> 3;
        if (gBattleWork->unk0B80 == 1)
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gBattleWork->unk0AE8.fields.unkB00[0] != NULL)
                sub_08031368(gBattleWork->unk0AE8.fields.unkB00, 8, &cx, &cy);
            gBattleWork->unk0B7C += (cx - gBattleWork->unk0B7C) >> 3;
        }
        else
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gBattleWork->unk0AE8.fields.unkB20[0] != NULL)
                sub_08031368(gBattleWork->unk0AE8.fields.unkB20, 8, &cx, &cy);
            gBattleWork->unk0B7C += (cx - gBattleWork->unk0B7C) >> 3;
        }
    }
    else
    {
        BtlClearState();
    }
}
