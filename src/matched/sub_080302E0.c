#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080302e0
/* match-compiler: old_agbcc */
/* Advance battler spin angle by speed/0x900 (direction from unk1F bit 6) and update its sprite. */
void sub_080302E0(struct Unk346C0 *a)
{
    s32 speed;
    s32 angle;
    s32 delta;
    struct BattleWork **work = gBattleWorkPtrLoc;
    struct BattleWork **dest;

    speed = (*work)->unk013C.values[a->unk30C];
    angle = (*work)->unk0AE8.words[a->unk30C];
    delta = _080740B0(speed << 16, 0x900);
    dest = work;
    if (a->unk04->unk28->unk1F & 0x40)
        angle -= delta;
    else
        angle += delta;
    (*dest)->unk0AE8.words[a->unk30C] = angle;
    angle = (angle >> 8) & 0xFF;
    if (a->unk00->unk00 != NULL)
    {
        if ((delta >> 8) > 0x1F)
            a->unk00->unk00->unk18 = RandRange(2);
        else
            a->unk00->unk00->unk18 = 2;
        if (a->unk00->unk00->unk30 != NULL)
            sub_08070354((struct Unk70354 *)a->unk00->unk00, a->unk00->unk00->unk30->unk14, a->unk00->unk00->unk30->unk16, angle);
    }
}

