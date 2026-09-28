#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803370c
/* match-compiler: old_agbcc */
// Tick the floating score digits (BattleWork+0xB54): count the shown value up
// towards its target by 4, lay the digits out right-to-left, ease y and x
// towards their targets, and clear the display once the timer runs out.
void BattleScorePopupTick(void)
{
    s32 count;
    s32 x;
    s32 i;

    if (gData_03000290->unk0B6C != 1)
        return;
    if (--gData_03000290->unk0B78 >= 0)
    {
        if (gData_03000290->unk0B64 < gData_03000290->unk0B68)
        {
            gData_03000290->unk0B64 += 4;
            if (gData_03000290->unk0B64 > gData_03000290->unk0B68)
                gData_03000290->unk0B64 = gData_03000290->unk0B68;
        }
        count = DigitSpritesSetValue((struct Sprite **)gData_03000290->unk0B54, gData_03000290->unk0B64, 4, gData_0810B4E0, 1);
        x = gData_03000290->unk0B7C + (count - 1) * 0x700;
        for (i = 0; i < count; i++)
        {
            struct Sprite *digit = gData_03000290->unk0B54[i];

            if (digit != NULL)
            {
                digit->unk08 = x;
                digit->unk0C = gData_03000290->unk0B74;
            }
            x -= 0x700;
        }
        gData_03000290->unk0B74 += (gData_03000290->unk0B70 - gData_03000290->unk0B74) >> 3;
        if (gData_03000290->unk0B80 == 1)
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB00[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB00, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->unk0B7C += (cx - gData_03000290->unk0B7C) >> 3;
        }
        else
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB20[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB20, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->unk0B7C += (cx - gData_03000290->unk0B7C) >> 3;
        }
    }
    else
    {
        BtlClearState();
    }
}

