#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08043c70
void sub_08043C70(s32 arg0, s32 arg1, u16 arg2, u16 arg3) {
    _08073C4C(arg1, gUnk_03000560, 0x84, *(s32 *)0x080BB8C0, (s32) arg2);
    sub_08043C28();
}

