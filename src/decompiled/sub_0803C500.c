#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803c500
void sub_0803C500(s32 arg0) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;

    temp_r6 = sub_0807309C(0x20);
    temp_r5 = sub_0807309C(0x20);
    sub_08061E8C(gBattleWork + 0x1F10, 0x080B72F3, 0x082BF600, 0xF0, 0x78);
    temp_r4 = 0x64 - arg0;
    sub_080735DC(temp_r4, temp_r5, 0x20);
    sub_08073AEC(*(0x080971EC + ((gMainWorkPtr)->unk1818 * 4)), temp_r6, temp_r5, 0x40, 0x20);
    sub_08061EF8(gBattleWork + 0x1F10, temp_r6, 0, 0x3E, 0, 0xFFFF, 0);
    sub_08073114(temp_r6);
    sub_08073114(temp_r5);
    sub_08067B98(0x0833C79C, temp_r4);
    (gBattleWork)->unk1F74 = (s16) (0x64 - arg0);
}

