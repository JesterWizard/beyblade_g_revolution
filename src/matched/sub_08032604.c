#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08032604
void sub_08032604(void)
{
    u8 mode;
    struct BattleWork *work;

    mode = _08032458();
    sub_08069894();
    gBattleWork->unk00 = sub_08065E0C(gBattleWork->filler_0008, 2, gData_0807800C[(s8)mode].layer0, 0x8000, 0);
    gBattleWork->unk04 = sub_08065E0C(gBattleWork->unk090, 3, gData_0807800C[(s8)mode].layer1, 0x8000, 0);
    sub_080679A4(gData_0807800C[(s8)mode].palette);
    BgSetPriorities(1, 2, 3, 0);
    REG_DISPCNT = 0x1C42;
    work = gBattleWork;
    work->unk054 = 0x10000;
    work->unk058 = 0x10000;
    work->unk050 = 60;
    work->unk052 = 60;
    work->unkDC = 0x10000;
    work->unkE0 = 0x10000;
    work->unkD8 = 60;
    work->unkDA = 60;
}


