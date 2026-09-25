#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033978
void sub_08033978(void *arg0, void *arg1, void *arg2, u8 arg3) {
    u8 temp_r6;

    temp_r6 = arg3;
    arg0->unk00 = 1;
    arg0->unk04 = arg1;
    arg0->unk08 = arg2;
    sub_08034FF8(arg1, *(0x08078158 + (temp_r6 * 4)));
    sub_08034FF8(arg2, 0x08078E58, arg1);
    BtlSetMode1F90(0x80);
    sub_08035204(arg1, 0, 0xC, -1);
    arg1->unk8C = sub_08067FC8(arg1 + 0x1C, 0);
    arg1->unk2B0 = 0;
    arg1->unk2B4 = -1;
    arg1->unk2CC = 2;
    arg1->unk310 = 1;
    arg2->unk2CC = 6;
    arg1->unk310 = 1;
    sub_08060254(0xB, 0x38, temp_r6);
    arg0->unk0D = 0;
}

