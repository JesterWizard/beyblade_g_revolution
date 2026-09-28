#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080333e4
/* match-compiler: old_agbcc */

void sub_08068584(void *a, s32 b, s32 c);

void sub_080333E4(void *arg, s32 x, s32 y, u8 mode)
{
    u16 id;

    if (mode > 4)
        return;
    if (gBattleWork->unk2088 == 1 && (s8)gBattleWork->unk2089 != mode)
        sub_08033574();
    if (gBattleWork->unk2088 == 0)
    {
        id = PaletteSlotAcquire(gData_08078108[mode]);
        sub_08067BB8((struct Unk67BB8 *)&gBattleWork->unk1FAC, gData_08078108[mode], 0, (s32)arg, x, y, -1);
        sub_08068584(&gBattleWork->unk1FAC, 0x20, 0x20);
        gBattleWork->unk201C = sub_08067FC8(&gBattleWork->unk1FAC, 0);
        gBattleWork->unk1FE6 = (gBattleWork->unk1FE6 & 1) | (id << 1);
        gBattleWork->unk2088 = 1;
    }
    else if ((s8)gBattleWork->unk2089 == mode)
    {
        gBattleWork->unk201C += sub_08067FC8(&gBattleWork->unk1FAC, 0);
    }
}

