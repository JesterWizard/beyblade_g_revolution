#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806121c
void sub_0806121C(void *arg0, s32 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    u16 temp_r4;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;
    void *temp_r3;

    sp4 = arg1;
    temp_r4 = arg2;
    spC = (s32) (u16) arg6;
    sp8 = (s32) (u16) (arg7 << 0xC);
    _08073C4C(0, gUnk_03000798, 0xAC, *(s32 *)0x080BB8BC);
    temp_r3 = gUnk_03000798;
    temp_r0 = temp_r3 + 0x88;
    temp_r3->unk88 = arg0;
    temp_r0_2 = temp_r0 + 4;
    temp_r0->unk04 = arg1;
    temp_r0_2->unk08 = temp_r4;
    (temp_r0_2 + 8)->unk02 = (u16) sp0.unk8;
    temp_r3->unkA0 = (u16) arg0->unk04;
    temp_r3->unkA2 = (s16) arg0->unk05;
    temp_r0_3 = temp_r3 + 0x90;
    temp_r3->unk90 = 0;
    temp_r0_4 = temp_r0_3 + 2;
    temp_r0_3->unk02 = 0;
    temp_r0_5 = temp_r0_4 + 0xA;
    temp_r0_4->unk0A = (s16) ((u16) temp_r3->unkA0 >> 2);
    temp_r0_5->unk08 = 0;
    (temp_r0_5 + 8)->unk02 = 0;
    sub_08068BD4(temp_r3, 3, temp_r4, 0);
    sp0 = (s32) (u16) (temp_r4 - 1);
    sub_08061628((u8) (u16) arg5, (u8) spC, (u8) arg3, (u8) (u16) arg4);
    sub_08061308();
}

