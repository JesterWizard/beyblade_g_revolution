#define sub_0802C4A4 sub_0802C4A4_old_proto
#include "global.h"
#undef sub_0802C4A4

struct Unk2C314Result
{
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    s32 unk04;
    struct Unk1694 *unk08;
};

struct Unk1694Bytes
{
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
};

s32 sub_0802C4A4(s8 a, s8 idx, struct Unk2C314Result *out)
{
    register u32 a_norm asm("r5");
    register s32 match_a asm("r12");
    register struct MainWork **main_loc asm("r3");
    register struct MainWork **loop_loc asm("r5");
    register u32 loop_offset asm("r6");
    register u32 index asm("r4");
    register struct Unk1694Bytes *entry asm("r0");
    register struct MainWork *work_ptr asm("r0");
    register struct Unk1694Bytes **table_loc asm("r1");
    register struct Unk1694Bytes *table_base asm("r1");
    register u32 scaled_index asm("r3");
    register u32 mask asm("r0");
    register u32 temp asm("r0");
    u32 offset;

    a_norm = ((u32)a << 24) >> 24;
    idx = ((u32)idx << 24) >> 24;
    if (out != 0)
    {
        out->unk04 = -1;
        mask = 0xFF;
        out->unk00 |= mask;
        out->unk03 |= mask;
        out->unk02 = 0;
        out->unk01 = 0;
        out->unk08 = 0;
    }
    main_loc = gMainWorkPtrLoc;
    offset = 0x1694;
    if ((*main_loc)->unk1694 != 0)
    {
        index = 0;
        temp = a_norm << 24;
        loop_loc = main_loc;
        loop_offset = offset;
        match_a = (s32)temp >> 24;
        temp = idx << 24;
        idx = (s32)temp >> 24;
        do
        {
            work_ptr = *loop_loc;
            table_loc = (struct Unk1694Bytes **)&work_ptr->unk1694;
            table_base = *table_loc;
            scaled_index = index << 2;
            entry = (struct Unk1694Bytes *)(
                (u8 *)table_base + scaled_index);
            if ((s32)(s8)entry->unk03 == match_a && index == idx)
            {
                if (out != 0)
                {
                    out->unk04 = index;
                    out->unk00 = ((struct Unk1694Bytes *)(
                        (u8 *)table_base + scaled_index))->unk00;
                    out->unk03 = ((struct Unk1694Bytes *)(
                        (u8 *)table_base + scaled_index))->unk03;
                    out->unk02 = ((struct Unk1694Bytes *)(
                        (u8 *)table_base + scaled_index))->unk02;
                    out->unk01 = ((struct Unk1694Bytes *)(
                        (u8 *)table_base + scaled_index))->unk01;
                    out->unk08 = (struct Unk1694 *)(
                        (u8 *)table_base + scaled_index);
                }
                return 1;
            }
            index++;
        } while (index <= 0x7F);
    }
    return 0;
}
