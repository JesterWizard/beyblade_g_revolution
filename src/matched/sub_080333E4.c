#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080333e4
/* match-compiler: old_agbcc */

void sub_08068584(void *a, s32 b, s32 c);

void BtlEffectStart(void *arg, s32 x, s32 y, u8 mode)
{
    u16 id;

    if (mode > 4)
        return;
    if (gBattleWork->effectActive == 1 && (s8)gBattleWork->effectMode != mode)
        BtlEffectStop();
    if (gBattleWork->effectActive == 0)
    {
        id = PaletteSlotAcquire(gData_08078108[mode]);
        AnimObjCreate((struct AnimObj *)&gBattleWork->effectObj, gData_08078108[mode], 0, (s32)arg, x, y, -1);
        sub_08068584(&gBattleWork->effectObj, 0x20, 0x20);
        gBattleWork->effectFramesLeft = AnimDurationForKey(&gBattleWork->effectObj, 0);
        gBattleWork->unk1FE6 = (gBattleWork->unk1FE6 & 1) | (id << 1);
        gBattleWork->effectActive = 1;
    }
    else if ((s8)gBattleWork->effectMode == mode)
    {
        gBattleWork->effectFramesLeft += AnimDurationForKey(&gBattleWork->effectObj, 0);
    }
}

