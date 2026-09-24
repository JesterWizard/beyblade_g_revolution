#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071ba0
void sub_08071BA0(void) {
    s32 temp_r5;
    void *temp_r1;

    *(s16 *)0x04000084 = 0x80;
    (void *)0x04000082->unk00 = 0xB04;
    temp_r1 = (void *)0x04000082 + 0x3A;
    temp_r5 = *(s32 *)gUnk_030040DC;
    (void *)0x04000082->unk3A = temp_r5;
    temp_r1->unk04 = 0x040000A0;
    (temp_r1 + 4)->unk04 = 0xB6000000;
    *(s32 *)0x04000104 = (*(u16 *)gUnk_030040D8 - 2) | 0xC40000;
    *(s32 *)0x04000100 = (0x10000 - _080741EC(0x01000000, *(s32 *)gUnk_03004100)) | 0x800000;
    *(s32 *)gUnk_030000B8 = temp_r5;
    *(s32 *)gUnk_030000BC = 0x10000 - *(u16 *)gUnk_0300410C;
}

