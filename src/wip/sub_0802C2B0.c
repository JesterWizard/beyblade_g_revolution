#define sub_0802C2B0 sub_0802C2B0_old_proto
#include "global.h"
#undef sub_0802C2B0

void sub_0802C2B0(u32 a, u32 b)
{
    register u32 value asm("r3");
    u32 key;
    register struct MainWork **loc asm("r12");
    register struct MainWork **loc_load asm("r1");
    register u32 index asm("r2");
    register u32 offset asm("r4");
    register struct MainWork **loop_loc asm("r6");
    register u32 loop_offset asm("r5");
    register u32 shifted_value asm("r0");
    register u32 scaled_index asm("r0");
    register u32 shifted_key asm("r1");
    register struct Unk1694 *final_base asm("r0");
    register u32 zero asm("r4");
    register struct Unk1694 *record_reg asm("r1");
    struct MainWork *work;
    register struct MainWork *final_work asm("r1");

    a = (a << 24) >> 24;
    value = a;
    b = (b << 16) >> 16;
    key = b;
    loc_load = gMainWorkPtrLoc;
    work = *loc_load;
    offset = 0x1694;
    loc = loc_load;
    if (work->unk1694 != 0)
    {
        index = 0;
        shifted_value = value << 24;
        loc = loc_load;
        loop_loc = loc;
        loop_offset = offset;
        value = (s32)shifted_value >> 24;
        zero = 0;
        do
        {
            record_reg = *(struct Unk1694 **)(
                (u8 *)(*loop_loc) + loop_offset);
            scaled_index = index << 2;
            record_reg = (struct Unk1694 *)(
                (u8 *)record_reg + scaled_index);
            if (record_reg->unk03 == value)
                record_reg->unk01 = zero;
            index++;
        } while (index <= 0x7F);
    }
    final_work = *loc;
    shifted_key = key << 16;
    final_base = final_work->unk1694;
    record_reg = (struct Unk1694 *)(
        (u8 *)final_base + ((s32)shifted_key >> 14));
    record_reg->unk01 = 1;
}
