#define sub_0802C62C sub_0802C62C_u8_proto
#include "global.h"
#undef sub_0802C62C

struct Unk1694Raw
{
    u32 raw;
};

struct Unk2BAD4Args
{
    u32 arg2;
    volatile u32 arg3;
};

void sub_0803DEC8(s8 a, s8 b, u8 c);
s32 sub_0802C62C(s8 a);

s32 sub_0802BAD4(u32 a, u32 b, u32 c, u32 d)
{
    register u32 arg0;
    register u32 arg1;
    register u32 index;
    register u32 shifted_arg1;
    register s32 signed_arg1;
    register s32 limit;
    register struct MainWork **main_loc;
    register struct MainWork *work;
    register u32 temp;
    register u32 init_offset;
    register u32 loop_offset;
    register u32 index_offset;
    struct Unk1694Raw *raw_slot;
    struct Unk1694 *table_base;
    struct Unk1694 *record;
    struct Unk2BAD4Args stack_args;
    volatile u32 saved_offset;
    register s32 scratch0;
    register s32 signed_arg0;
    register s32 result;

    a = (a << 24) >> 24;
    arg0 = a;
    b = (b << 24) >> 24;
    arg1 = b;
    c = (c << 24) >> 24;
    stack_args.arg2 = c;
    d = (d << 24) >> 24;
    stack_args.arg3 = d;
    main_loc = gMainWorkPtrLoc;
    init_offset = 0x1694;
    work = *main_loc;
    if (*(struct Unk1694 **)((u8 *)work + init_offset) == 0)
        return 0;
    temp = arg1;
    shifted_arg1 = temp << 24;
    signed_arg1 = (s32)shifted_arg1 >> 24;
    limit = sub_0802C62C((s8)signed_arg1);
    if (limit >= _0802BA7C((s8)signed_arg1))
        return 0;
    index = 0;
    loop_offset = 0x1694;
    do
    {
        work = *main_loc;
        table_base = *(struct Unk1694 **)((u8 *)work + loop_offset);
        index_offset = index << 2;
        raw_slot = (struct Unk1694Raw *)((u8 *)table_base + index_offset);
        if (raw_slot->raw == 0xFF0000FF)
        {
            scratch0 = (s32)shifted_arg1 >> 24;
            if (scratch0 == 1)
            {
                temp = arg0;
                scratch0 = temp << 24;
                signed_arg0 = scratch0 >> 24;
                saved_offset = loop_offset;
                result = sub_0802C3DC(1, (s8)signed_arg0, 0);
                if (result != 0)
                {
                    sub_08067B98((void *)0x0833BE1C, signed_arg0);
                    return 1;
                }
                sub_0803DEC8(
                    (s8)signed_arg0,
                    (s8)stack_args.arg3,
                    (u8)index);
                loop_offset = saved_offset;
                record = (struct Unk1694 *)(
                    (u8 *)(*main_loc) + loop_offset + index_offset);
                record->unk02 = (u8)result;
            }
            record = (struct Unk1694 *)(
                (u8 *)(*main_loc) + loop_offset + index_offset);
            record->unk00 = (u8)arg0;
            record = (struct Unk1694 *)(
                (u8 *)(*main_loc) + loop_offset + index_offset);
            record->unk03 = (u8)arg1;
            record = (struct Unk1694 *)(
                (u8 *)(*main_loc) + loop_offset + index_offset);
            record->unk01 = (u8)stack_args.arg2;
            record = (struct Unk1694 *)(
                (u8 *)(*main_loc) + loop_offset + index_offset);
            record->unk02 = (u8)stack_args.arg3;
            return 1;
        }
        index++;
    } while (index <= 0x7F);
    return 0;
}
