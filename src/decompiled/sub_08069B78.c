#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069b78
void sub_08069B78(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *temp_r0;
    u8 *temp_r0_2;
    u8 *temp_r0_3;
    u8 *temp_r0_4;

    temp_r0 = sub_08069988(0);
    *temp_r0 = (-4 & *temp_r0) | (arg0 & 3);
    temp_r0_2 = sub_08069988(1);
    *temp_r0_2 = (-4 & *temp_r0_2) | (arg1 & 3);
    temp_r0_3 = sub_08069988(2);
    *temp_r0_3 = (-4 & *temp_r0_3) | (arg2 & 3);
    temp_r0_4 = sub_08069988(3);
    *temp_r0_4 = (-4 & *temp_r0_4) | (arg3 & 3);
}

