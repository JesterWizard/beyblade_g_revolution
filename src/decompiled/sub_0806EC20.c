#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806ec20
void sub_0806EC20(void *arg0, s32 arg1, u16 arg2, s32 arg3) {
    s32 sp0;
    s32 spC;
    s32 sp10;
    s32 sp14;
    void *sp18;
    s32 sp1C;
    s32 sp20;
    s32 temp_r3;

    sp10 = arg3;
    spC = (s32) arg2;
    sp14 = 0;
    arg0->unk220 = arg1;
    arg0->unk224 = sp14;
    arg0->unk354 = (u8) (-2 & arg0->unk354);
    arg0->unk344 = sp14;
    arg0->unk348 = sp14;
    arg0->unk355 = 0xF;
    arg0->unk356 = 0xFF;
    arg0->unk35C = (s16) sp14;
    arg0->unk35E = (u16) sp0.unk14;
    arg0->unk360 = 0xF0;
    arg0->unk362 = 0xA0;
    arg0->unk364 = sp14;
    arg0->unk368 = sp14;
    *(s16 *)0x04000050 = 0x3FFF;
    sub_08069894();
    sp18 = arg0;
    temp_r3 = arg1 + 0x14;
    sp1C = temp_r3;
    sp20 = temp_r3;
}

