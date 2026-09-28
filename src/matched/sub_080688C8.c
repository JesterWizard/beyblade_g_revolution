#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080688c8
// Load a BG tile map, set the scroll registers to (x, y), and seed the
// visible tile rect (x/8, y/8, width 1<<unk5F, height 1<<unk60).
void BgMapInit(struct Unk68988 *state, u8 index, void *arg2, u16 limit, u16 mode, s32 x, s32 y)
{
    struct Unk688C8Rect *rect;
    s32 xt = x >> 3;
    s32 yt = y >> 3;
    s32 w, h;

    AffineBgLoad((struct Unk68E54 *)state, index, arg2, limit, mode);
    *BgGetHofsReg(index) = x;
    *BgGetVofsReg(index) = y;
    rect = state->unk08;
    rect->unk10 = xt;
    rect->unk14 = yt;
    rect->unk00 = xt;
    rect->unk08 = xt + (1 << state->unk5F) - 1;
    rect->unk04 = yt;
    rect->unk0C = yt + (1 << state->unk60) - 1;
    state->unk0C = x << 8;
    state->unk10 = y << 8;
    state->unk40 = x << 8;
    state->unk44 = y << 8;
    w = 1 << state->unk5F;
    h = 1 << state->unk60;
    if (!(mode & 2))
        BgMapBlitRect(state, rect->unk00, rect->unk04, rect->unk10, rect->unk14, w, h);
}

