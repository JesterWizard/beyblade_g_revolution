#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804ac3c
void sub_0804AC3C(void *arg0) {
    u8 temp_r4;
    u8 temp_r5;

    temp_r5 = arg0->unk2D5;
    temp_r4 = arg0->unk2FC;
    sub_08061BE8();
    sub_0804AAF0(arg0);
    sub_08061D68((u32) (((s32) (temp_r4 << 0x18) >> 8) + 0x70000) >> 0x10, 0xF, 4, 0x19);
    sub_08061D68((u32) (((s32) (temp_r5 << 0x18) >> 8) + 0x70000) >> 0x10, 0xE, 4, 0x19);
    sub_080674B4();
    _08073C40(*(s32 *)0x080BB888);
    sub_0804AE94();
}

