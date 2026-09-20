#define sub_0802C314 sub_0802C314_old_proto
#include "global.h"
#undef sub_0802C314

struct Unk2C314Result
{
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    s32 unk04;
    struct Unk1694 *unk08;
};

s32 sub_0802C314(s8 a, u8 b, struct Unk2C314Result *out)
{
    register u32 a_norm asm("r4");
    register u32 b_norm asm("r12");
    register s32 match_a asm("r8");
    register s32 match_b asm("r12");
    register struct MainWork **main_loc asm("r3");
    register struct MainWork **loop_loc asm("r6");
    register u32 loop_offset asm("r7");
    register u32 index asm("r5");
    register struct Unk1694 **table_loc asm("r4");
    register struct Unk1694 *entry asm("r3");
    register struct MainWork *work_ptr asm("r0");
    register struct Unk1694 *table_base asm("r0");
    register u32 scaled_index asm("r1");
    u32 offset;
    u32 temp;

    a_norm = ((u32)a << 24) >> 24;
    b_norm = ((u32)b << 24) >> 24;
    if (out != 0)
    {
        out->unk04 = -1;
        out->unk00 |= 0xFF;
        out->unk03 |= 0xFF;
        out->unk02 = 0;
        out->unk01 = 0;
        out->unk08 = 0;
    }
    main_loc = gMainWorkPtrLoc;
    offset = 0x1694;
    if ((*main_loc)->unk1694 != 0)
    {
        index = 0;
        loop_loc = main_loc;
        loop_offset = offset;
        temp = a_norm << 24;
        match_a = (s32)temp >> 24;
        temp = b_norm;
        match_b = (s32)(temp << 24) >> 24;
        do
        {
            work_ptr = *loop_loc;
            table_loc = &work_ptr->unk1694;
            table_base = *table_loc;
            scaled_index = index << 2;
            entry = (struct Unk1694 *)(
                (u8 *)table_base + scaled_index);
            if (entry->unk03 == match_a && entry->unk01 == match_b)
            {
                if (out != 0)
                {
                    out->unk04 = index;
                    out->unk00 = ((struct Unk1694 *)(
                        (u8 *)*table_loc + scaled_index))->unk00;
                    out->unk03 = ((struct Unk1694 *)(
                        (u8 *)(*loop_loc)->unk1694 + scaled_index))->unk03;
                    out->unk02 = ((struct Unk1694 *)(
                        (u8 *)(*loop_loc)->unk1694 + scaled_index))->unk02;
                    out->unk01 = ((struct Unk1694 *)(
                        (u8 *)(*loop_loc)->unk1694 + scaled_index))->unk01;
                    out->unk08 = (struct Unk1694 *)(
                        (u8 *)(*loop_loc)->unk1694 + scaled_index);
                }
                return 1;
            }
            index++;
        } while (index <= 0x7F);
    }
    return 0;
}
