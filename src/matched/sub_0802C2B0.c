#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c2b0
void sub_0802C2B0(u8 a, u16 i)
{
    u32 value;
    u32 key;
    u32 av;
    u32 iv;
    struct MainWork **loc;
    struct MainWork **loc_load;
    s32 index;
    u32 offset;
    struct MainWork **loop_loc;
    u32 loop_offset;
    u32 shifted_value;
    u32 scaled_index;
    u32 shifted_key;
    struct CollectionEntry *final_base;
    u32 zero;
    struct CollectionEntry *record_reg;
    struct MainWork *work;
    struct MainWork *final_work;
    u32 probe;

    av = a;
    av = (av << 24) >> 24;
    value = av;
    iv = i;
    iv = (iv << 16) >> 16;
    key = iv;
    loc_load = gMainWorkPtrLoc;
    work = *loc_load;
    offset = 0x1694;
    probe = (u32)work->unk1694;
    loc = loc_load;
    if (probe != 0)
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
            struct CollectionEntry *base;

            base = *(struct CollectionEntry **)((u8 *)(*loop_loc) + loop_offset);
            scaled_index = index << 2;
            record_reg = (struct CollectionEntry *)(scaled_index + (u32)base);
            if ((s8)record_reg->group == value)
                record_reg->slot = zero;
            index++;
        } while (index <= 0x7F);
    }
    final_work = *loc;
    shifted_key = key << 16;
    final_base = final_work->unk1694;
    record_reg = (struct CollectionEntry *)(((s32)shifted_key >> 14) + (u32)final_base);
    record_reg->slot = 1;
}

