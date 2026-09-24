#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060c30
void sub_08060C30(void *arg0, void *arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    void *sp8;
    s32 spC;
    s32 sp10;
    u16 temp_r4;
    u8 temp_r1;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;

    sp8 = arg1;
    spC = arg2;
    temp_r4 = arg3;
    temp_r1 = (u8) arg9;
    sp10 = (s32) temp_r1;
    _08073C4C(0, arg0, 0xAC, *(s32 *)0x080BB8BC);
    temp_r0 = arg0 + 0x88;
    arg0->unk88 = arg1;
    temp_r0_2 = temp_r0 + 4;
    temp_r0->unk04 = spC;
    temp_r0_2->unk08 = temp_r4;
    (temp_r0_2 + 8)->unk02 = (u16) (arg8 << 0xC);
    arg0->unkA0 = (u16) sp8->unk04;
    arg0->unkA2 = (s16) sp8->unk05;
    temp_r0_3 = arg0 + 0x90;
    arg0->unk90 = 0;
    temp_r0_4 = temp_r0_3 + 2;
    temp_r0_3->unk02 = 0;
    temp_r0_5 = temp_r0_4 + 0xA;
    temp_r0_4->unk0A = (s16) ((u16) arg0->unkA0 >> 2);
    temp_r0_5->unk08 = 0;
    (temp_r0_5 + 8)->unk02 = 0;
    sub_08068BD4(arg0, temp_r1, temp_r4, 0);
    sub_08060D58(arg0, (u8) (u16) arg6, (u8) (u16) arg7, (u8) (u16) arg4, (s32) (u8) (u16) arg5, (s32) (u16) (temp_r4 - 1));
    sub_08060D28(arg0);
}

