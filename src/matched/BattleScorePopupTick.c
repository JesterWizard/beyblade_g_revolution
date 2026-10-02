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

    if (gData_03000290->popupActive != 1)
        return;
    if (--gData_03000290->popupTimer >= 0)
    {
        if (gData_03000290->popupShown < gData_03000290->popupTarget)
        {
            gData_03000290->popupShown += 4;
            if (gData_03000290->popupShown > gData_03000290->popupTarget)
                gData_03000290->popupShown = gData_03000290->popupTarget;
        }
        count = DigitSpritesSetValue((struct Sprite **)gData_03000290->popupDigits, gData_03000290->popupShown, 4, gData_0810B4E0, 1);
        x = gData_03000290->popupX + (count - 1) * 0x700;
        for (i = 0; i < count; i++)
        {
            struct Sprite *digit = gData_03000290->popupDigits[i];

            if (digit != NULL)
            {
                digit->unk08 = x;
                digit->unk0C = gData_03000290->popupY;
            }
            x -= 0x700;
        }
        gData_03000290->popupY += (gData_03000290->popupTargetY - gData_03000290->popupY) >> 3;
        if (gData_03000290->popupSide == 1)
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB00[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB00, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->popupX += (cx - gData_03000290->popupX) >> 3;
        }
        else
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB20[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB20, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->popupX += (cx - gData_03000290->popupX) >> 3;
        }
    }
    else
    {
        BattleScorePopupClear();
    }
}

