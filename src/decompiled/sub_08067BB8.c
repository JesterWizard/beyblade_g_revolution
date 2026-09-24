#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067bb8
void sub_08067BB8(struct Unk67BB8 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    void *temp_r0;
    void *temp_r0_10;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;
    void *temp_r0_6;
    void *temp_r0_7;
    void *temp_r0_8;
    void *temp_r0_9;

    arg0->unk00 = arg1;
    arg0->unk58 = (s32) (s32)gUnk_03000180;
    arg0->unk3C = arg2;
    arg0->unk70 = arg6;
    arg0->unk04 = (s32) (arg3 << 8);
    arg0->unk08 = (s32) (arg4 << 8);
    arg0->unk0C = (s32) (arg5 << 8);
    arg0->unk16 = 0;
    arg0->unk12 = 0x100;
    arg0->unk14 = 0x100;
    temp_r0 = arg0 + 0xA0;
    arg0->unkA0 = 0;
    temp_r0_2 = temp_r0 + 2;
    temp_r0->unk02 = 0;
    temp_r0_2->unk02 = 0;
    (temp_r0_2 + 2)->unk01 = 0;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    arg0->unk48 = 0;
    arg0->unk4C = 0;
    arg0->unk50 = 0;
    arg0->unk54 = 0;
    arg0->unk68 = 0x10;
    arg0->unk18 = 0;
    arg0->unk64 = 0;
    arg0->unk22 = 0;
    arg0->unk60 = (u16) (arg0->unk60 | 0xFFFF);
    arg0->unk1A = (u16) (arg0->unk1A | 0xFFFF);
    arg0->unk1C = 0;
    arg0->unk1E = 0;
    arg0->unk20 = 0;
    arg0->unk2C = 0;
    arg0->unk2E = (u16) (0xFFFF | arg0->unk2E);
    arg0->unk10 = (u8) arg1->unk04;
    arg0->unk11 = (u8) arg1->unk05;
    arg0->unk30 = (u8) arg1->unk06;
    arg0->unk2A = (s16) arg1->unk08;
    arg0->unk38 = (u8) arg1->unk07;
    arg0->unk28 = (s16) arg1->unk14;
    temp_r0_3 = arg0 + 0x31;
    arg0->unk31 = 0;
    temp_r0_3->unk08 = 0;
    (temp_r0_3 + 8)->unk02 = 0;
    arg0->unk3A = (u8) arg1->unk0C;
    arg0->unk6C = 0;
    arg0->unk74 = -1;
    arg0->unk78 = 0;
    arg0->unk7C = 0;
    temp_r0_4 = arg0 + 0x80;
    arg0->unk80 = 0;
    temp_r0_5 = temp_r0_4 + 4;
    temp_r0_4->unk04 = -1;
    temp_r0_6 = temp_r0_5 + 4;
    temp_r0_5->unk04 = 0;
    temp_r0_7 = temp_r0_6 + 4;
    temp_r0_6->unk04 = 0;
    temp_r0_8 = temp_r0_7 + 1;
    temp_r0_7->unk01 = 0;
    temp_r0_8->unk0B = 0;
    temp_r0_9 = (temp_r0_8 + 0xB) - 8;
    temp_r0_9->unk00 = 0;
    temp_r0_10 = temp_r0_9 + 4;
    temp_r0_9->unk04 = 0;
    temp_r0_10->unk1C = 0;
    (temp_r0_10 + 0x1C)->unk04 = 0;
    sub_08068574(arg0, (u8) arg0->unk10 >> 1, arg0->unk11, 0);
    sub_08068558(arg0, 0, 0, arg0->unk10, (s32) arg0->unk11);
    arg0->unkB8 = 0;
    (arg0 + 0xB8)->unk04 = 0;
    sub_08068180(arg0, 0);
    arg0->unkC0 = 0;
}

