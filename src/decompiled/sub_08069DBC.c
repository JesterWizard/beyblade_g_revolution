#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069dbc
#include "global.h"

/* match-compiler: old_agbcc */
// @ 0x08069dbc
// Copy `count` halfwords from a source map into VRAM with row/column strides.
void sub_08069DBC(struct Unk69DBC *state, u32 unused, u32 count_arg, u32 destination_arg, u32 shift_arg, u32 source_arg)
{
    u8 count;
    s32 source_index;
    u32 stride;
    u16 *source;
    u16 *destination;
    u8 *shift_ptr;
    u32 off;
    u32 source_step;
    u32 two;

    count = (u8)count_arg;
    source_index = (s32)source_arg;
    destination = (u16 *)(state->unk70 + ((source_index & 0x1F) << 1));
    source = destination;
    source_index >>= 5;
    stride = state->unk00;
    source = (u16 *)((u8 *)source + ((stride << 2) * source_index));
    off = state->unk5C << 11;
    off += 0x6000000;
    off += ((shift_arg << state->unk5F) + destination_arg) << 1;
    destination = (u16 *)off;
    if (count != 0)
    {
        source_step = stride << 1;
        shift_ptr = &state->unk5F;
        two = 2;
        do
        {
            *destination = *source;
            source = (u16 *)((u8 *)source + source_step);
            destination = (u16 *)((u8 *)destination + (two << *shift_ptr));
            count--;
        } while (count != 0);
    }
}

