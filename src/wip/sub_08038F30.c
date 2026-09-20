#include "global.h"

void sub_08038F30(s32 mode)
{
    register struct BattleWork **battle_loc asm("r6");
    register struct Unk002A0 *table asm("r7");
    register struct MainWork **main_loc asm("r5");
    s32 i;
    struct Unk38F30Slot *slot;

    if (mode == -1)
        goto negative;
    if (mode == 1)
        goto positive;
    goto done;

negative:
    i = 0;
    battle_loc = gBattleWorkPtrLoc;
    table = &gUnk_030002A0;
    main_loc = gMainWorkPtrLoc;
    while (i <= 3)
    {
        (*main_loc)->unk07A4[i]->unk0C -= 0x400;
        i++;
    }
    (*battle_loc)->unk324->unk0C -= 0x400;
    if (table->records[(s8)(*battle_loc)->unk12F].unk1C == 0)
    {
        slot = (struct Unk38F30Slot *)&(*battle_loc)->unk023C[0];
        i = 3;
        while (i >= 0)
        {
            sub_08070C98(&slot->position, 0, -4);
            slot++;
            i--;
        }
    }
    else
        sub_080620D4(&(*battle_loc)->unk2FC, 0, -4);
    goto done;

positive:
    i = 0;
    battle_loc = gBattleWorkPtrLoc;
    table = &gUnk_030002A0;
    main_loc = gMainWorkPtrLoc;
    while (i <= 3)
    {
        (*main_loc)->unk07A4[i]->unk0C += 0x400;
        i++;
    }
    (*battle_loc)->unk324->unk0C += 0x400;
    if (table->records[(s8)(*battle_loc)->unk12F].unk1C == 0)
    {
        slot = (struct Unk38F30Slot *)&(*battle_loc)->unk023C[0];
        i = 3;
        while (i >= 0)
        {
            sub_08070C98(&slot->position, 0, 4);
            slot++;
            i--;
        }
    }
    else
        sub_080620D4(&(*battle_loc)->unk2FC, 0, 4);

done:
    return;
}
