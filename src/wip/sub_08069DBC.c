#include "global.h"

void sub_08069DBC(
    struct Unk69DBC *state,
    u32 unused,
    u32 count_arg,
    u32 destination_arg,
    u32 shift_arg,
    u32 source_arg)
{
    u8 count;
    u32 source_index;
    u16 *source;
    u16 *destination;

    count = (u8)count_arg;
    source_index = source_arg;
    source = (u16 *)(state->unk70
        + ((source_index & 0x1F) << 1)
        + ((state->unk00 << 2) * (source_index >> 5)));
    destination = (u16 *)(VRAM
        + (state->unk5C << 11)
        + (((shift_arg << state->unk5F) + destination_arg) << 1));
    while (count != 0)
    {
        *destination = *source;
        source += state->unk00;
        destination += 1 << state->unk5F;
        count--;
    }
}
