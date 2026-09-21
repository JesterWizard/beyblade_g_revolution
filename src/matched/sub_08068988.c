#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068988
#include "global.h"

// @ 0x08068988
// Set up one tile-map blit: reset both per-slot state words, forward the args to
// sub_08068A08, then clamp a 1<<unk5F x 1<<unk60 rect to the state's own size.
// `width`/`height` MUST be signed: retail emits `bge` (signed) for both clamps,
// unsigned locals make agbcc emit `bcs`. Same 126 bytes either way; only the
// branch opcode differs.
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
    s32 width;
    s32 height;

    index = (u8)index_arg;
    limit = (u16)limit_arg;
    mode = (u16)mode_arg;
    sub_08068A08(state, index, (void *)unused, limit, mode);
    *sub_08069908(index) = 0;
    *sub_08069948(index) = 0;
    width = 1 << state->unk5F;
    height = 1 << state->unk60;
    if (state->unk00 < width)
        width = state->unk00;
    if (state->unk04 < height)
        height = state->unk04;
    if ((mode & 2) == 0)
        sub_08069270(state, 0, 0, 0, 0, width, height);
}

