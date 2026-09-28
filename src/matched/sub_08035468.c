#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035468
// Projects world point (x, y, z) through the battle camera (gBattleWork.unkAA8:
// position, screen centre, angle) and places the source's sprite there: depth
// scales the offset, the sprite offset (ox, oy) is rotated by camera - angle, and
// sub_08070354 gets the depth as scale and the relative angle.
void BtlPlaceSpriteAtWorld(void *source, s32 x, s32 y, s32 z, s32 ox, s32 oy, s32 angle)
{
    struct Unk70354 *obj = ((struct Unk35468Source *)source)->unkB8;
    struct Unk30638AA8 *cam = &gBattleWork->unkAA8;
    s32 sine;
    s32 cosine;
    s32 sx;
    s32 sy;
    s32 edge;
    s32 rx;
    s32 ry;
    s32 depth;

    if (obj == NULL)
        return;
    sine = gData_083C9544[((u32)cam->unk14 & 0xFFFF) >> 8];
    cosine = gData_083C9544[(((u32)cam->unk14 & 0xFFFF) >> 8) + 0x40];
    x -= cam->unk00;
    y -= cam->unk04;
    z -= cam->unk08;
    depth = z >> 8;
    x = (x * depth) >> 8;
    y = (y * depth) >> 8;
    sx = ((x * cosine) >> 8) + ((y * sine) >> 8) + cam->unk0C;
    sy = ((y * cosine) >> 8) - ((x * sine) >> 8) + cam->unk10;
    edge = (depth << 13) >> 8;
    sx -= edge;
    sy -= edge;
    if (depth < 0x100)
    {
        edge = ((0x100 - depth) << 13) >> 8;
        sx -= edge;
        sy -= edge;
    }
    cosine = gData_083C9544[(((u32)(cam->unk14 - angle) & 0xFFFF) >> 8) + 0x40];
    sine = gData_083C9544[((u32)(cam->unk14 - angle) & 0xFFFF) >> 8];
    rx = ((ox * cosine) >> 8) + ((oy * sine) >> 8);
    ry = ((oy * cosine) >> 8) - ((ox * sine) >> 8);
    rx = (rx * depth) >> 8;
    ry = (ry * depth) >> 8;
    obj->unk08 = sx - rx;
    obj->unk0C = sy - ry;
    SpriteApplyAffine(obj, depth, depth, (angle - cam->unk14) >> 8);
}

