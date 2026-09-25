#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* match-compiler: old_agbcc */

void sub_080688C8(
    struct Unk68988 *state,
    u32 index_arg,
    u32 unused,
    u32 limit_arg,
    u32 mode_arg,
    s32 x,
    s32 y)
{
    struct Unk68988 *stateReg;
    u8 index;
    u16 limit;
    u16 mode;
    u32 modeRaw;
    s32 xTile;
    s32 yTile;
    struct Unk688C8Rect *rect;
    u8 *shiftW;
    u8 *shiftH;
    u32 one;
    s32 w;
    s32 h;
    s32 x8;
    s32 y8;

    stateReg = state;
    modeRaw = mode_arg;
    index = (u8)index_arg;
    limit = (u16)limit_arg;
    mode = (u16)modeRaw;
    xTile = x >> 3;
    yTile = y >> 3;

    sub_08068A08(stateReg, index, (void *)unused, limit, mode);
    *BgGetHofsReg(index) = (u16)x;
    *BgGetVofsReg(index) = (u16)y;

    rect = stateReg->unk08;
    rect->unk10 = xTile;
    rect->unk14 = yTile;
    rect->unk00 = xTile;
    shiftW = &stateReg->unk5F;
    one = 1;
    xTile += one << *shiftW;
    xTile -= 1;
    rect->unk08 = xTile;
    rect->unk04 = yTile;
    shiftH = &stateReg->unk60;
    yTile += one << *shiftH;
    yTile -= 1;
    rect->unk0C = yTile;

    x8 = x << 8;
    stateReg->unk0C = x8;
    y8 = y << 8;
    stateReg->unk10 = y8;
    stateReg->unk40 = x8;
    stateReg->unk44 = y8;

    w = one << *shiftW;
    h = one << *shiftH;
    if ((mode & 2) == 0)
        sub_08069270(stateReg, rect->unk00, rect->unk04, rect->unk10, rect->unk14, w, h);
}
