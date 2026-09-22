#include "global.h"

void sub_08068988(
    struct Unk68988 *state,
    u32 index_arg,
    u32 unused,
    u32 limit_arg,
    u32 mode_arg)
{
    u8 index;
    u16 limit;
    u16 mode;
    u32 width;
    u32 height;

    index = (u8)index_arg;
    limit = (u16)limit_arg;
    mode = (u16)mode_arg;
    sub_08068A08(state, index, (void *)unused, limit, mode);
    *BgGetHofsReg(index) = 0;
    *BgGetVofsReg(index) = 0;
    width = 1 << state->unk5F;
    height = 1 << state->unk60;
    if (state->unk00 < width)
        width = state->unk00;
    if (state->unk04 < height)
        height = state->unk04;
    if ((mode & 2) == 0)
        sub_08069270(state, 0, 0, 0, 0, width, height);
}
