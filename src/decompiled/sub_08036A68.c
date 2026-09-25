#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08036a68
void sub_08036A68(s32 arg0, u8 arg2) {
    s32 spC;
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r8;
    s32 temp_r9;

    temp_r9 = BtlObjTableAdd(0x80);
    temp_r8 = BtlObjTableAdd(0x80);
    temp_r0 = BtlObjTableAdd(0x80);
    spC = temp_r0;
    sub_08037318(arg0, arg2);
    sub_08061E8C((s32)gBattleWork + 0x14C, 0x080B72F3, 0x082BF600, 0xB0, 0x150);
    temp_r4 = arg2 * 0x2C;
    sub_08073AEC(*(0x080972A0 + ((gMainWorkPtr)->unk1818 * 4)), temp_r9, sub_08042B00(*(gUnk_030002A0 + temp_r4)), 0x23, 0x80);
    sub_08073AEC(temp_r9, temp_r8, sub_0803DD88(*(gUnk_030002A4 + temp_r4)), 0x40, 0x80);
    sub_08061EF8((s32)gBattleWork + 0x14C, temp_r8, 0, 0x50, 0, 0xC8, 0);
    BtlObjTableRemove(temp_r9);
    BtlObjTableRemove(temp_r8);
    BtlObjTableRemove(temp_r0);
    sub_08037430();
}

