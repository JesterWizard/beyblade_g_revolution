#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080523a4
void sub_080523A4(void *arg0) {
    sub_08061BE8();
    sub_0805264C(arg0, 0);
    sub_0805264C(arg0, 1);
    sub_0805264C(arg0, 2);
    sub_0805264C(arg0, 3);
    sub_0805264C(arg0, 4);
    sub_0805264C(arg0, 5);
    arg0->unk288->unk0C = (s32) ((M2C_ERROR(/* unknown instruction: ldsb $r0, ($mem_loc_fictive_) */) << 0xC) + 0x2C00);
    arg0->unk28C->unk0C = (s32) ((M2C_ERROR(/* unknown instruction: ldsb $r0, ($mem_loc_fictive_) */) << 0xC) + 0x2C00);
}

