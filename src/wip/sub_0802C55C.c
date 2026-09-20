#define sub_0802C55C sub_0802C55C_old_proto
#include "global.h"
#undef sub_0802C55C

void sub_0802C55C(s16 a, s8 b, s16 i)
{
    u32 key;
    register u32 b_norm asm("r12");
    register s32 index asm("r4");
    register struct MainWork **main_loc asm("r6");
    register u32 offset asm("r5");
    register u32 scaled_index asm("r2");
    register struct Unk1694 *entry asm("r3");
    s32 old_flag;
    register u32 mask asm("r1");
    register u32 temp asm("r0");

    key = ((u32)a << 16) >> 16;
    b_norm = ((u32)b << 24) >> 24;
    index = ((s32)i << 16) >> 16;
    if (index > 0x7F)
        return;

    main_loc = gMainWorkPtrLoc;
    offset = 0x1694;
    entry = (*main_loc)->unk1694 + index;
    scaled_index = index << 2;
    if (entry->unk00 != (s32)(s16)key)
        return;
    old_flag = entry->unk03;
    temp = b_norm << 24;
    if (old_flag != (s32)temp >> 24)
        return;

    mask = 0xFF;
    entry->unk00 |= mask;
    entry = (*main_loc)->unk1694 + index;
    entry->unk03 |= mask;
    entry = (*main_loc)->unk1694 + index;
    entry->unk02 = 0;
    entry = (*main_loc)->unk1694 + index;
    entry->unk01 = 0;
    if (old_flag == 1)
        sub_0803E0CC(index);
}
