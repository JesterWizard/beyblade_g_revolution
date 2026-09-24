#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08032604
void sub_08032604(void) {
    s32 temp_r5;
    u8 temp_r4;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;
    void *temp_r3;

    temp_r4 = _08032458();
    sub_08069894();
    temp_r5 = (s8) temp_r4 * 0xC;
    temp_r0 = gBattleWork;
    temp_r0->unk00 = sub_08065E0C(gBattleWork + 8, 2, *(0x0807800C + temp_r5), 0x8000, 0);
    (gBattleWork)->unk04 = sub_08065E0C(temp_r0 + 0x90, 3, *(0x08078010 + temp_r5), 0x8000, 0);
    sub_080679A4(*(0x08078014 + temp_r5));
    sub_08069B78(1, 2, 3, 0);
    *(s16 *)0x04000000 = 0x1C42;
    temp_r3 = gBattleWork;
    temp_r3->unk54 = 0x10000;
    temp_r3->unk58 = 0x10000;
    temp_r0_2 = temp_r3 + 0x50;
    temp_r3->unk50 = 0x3C;
    temp_r0_3 = temp_r0_2 + 2;
    temp_r0_2->unk02 = 0x3C;
    temp_r0_4 = temp_r0_3 + 0x8A;
    temp_r0_3->unk8A = 0x10000;
    temp_r0_4->unk04 = 0x10000;
    temp_r0_5 = (temp_r0_4 + 4) - 8;
    temp_r0_5->unk00 = 0x3C;
    temp_r0_5->unk02 = 0x3C;
}

