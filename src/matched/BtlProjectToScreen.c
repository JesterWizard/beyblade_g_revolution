#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035d68
/* match-compiler: old_agbcc */
// Project `source` (world x/y/z) into screen space relative to camera `state`:
// rotate by the camera angle, scale by depth, then place and scale the
// source's sprite (sub_08070354 with the depth as zoom).
void BtlProjectToScreen(struct Unk35D68Source *source, struct Unk35D68State *state)
{
    s16 index;
    s32 sine;
    s32 cosine;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 x;
    s32 y;
    s32 flag;

    flag = 0;
    index = state->unk14 >> 8;
    sine = gData_083C9544[index];
    cosine = gData_083C9544[index + 0x40];
    dx = source->unk0C - state->unk00;
    dy = source->unk10 - state->unk04;
    dz = (source->unk14 - state->unk08) >> 8;
    dx = (dx * dz) >> 8;
    dy = (dy * dz) >> 8;
    x = ((dx * cosine) >> 8) + ((sine * dy) >> 8) + state->unk0C;
    y = ((dy * cosine) >> 8) - ((sine * dx) >> 8) + state->unk10;
    x -= source->unk04;
    y -= source->unk08;
    if (dz > 0x100)
    {
        x -= (source->unk04 * (dz - 0x100)) >> 8;
        y -= ((dz - 0x100) * source->unk08) >> 8;
    }
    source->unk00->unk08 = x;
    source->unk00->unk0C = y;
    if (source->unk00->unk30 != NULL)
        flag = source->unk00->unk30->angle;
    SpriteApplyAffine((struct Unk70354 *)source->unk00, dz, dz, flag);
}

