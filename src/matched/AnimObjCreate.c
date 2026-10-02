#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067bb8
/* match-compiler: old_agbcc */
// Construct an animated object from its template: position (x, y, z in pixels,
// stored 24.8), defaults for every state field, then frame/palette setup.
void AnimObjCreate(struct AnimObj *obj, struct Unk67BB8Source *src, s32 arg2, s32 x, s32 y, s32 z, s32 arg6)
{
    obj->data = src;
    obj->lastAdvanceTick = gUnk_03000180.unk00;
    obj->unk3C = arg2;
    obj->countdown = arg6;
    obj->x = x << 8;
    obj->y = y << 8;
    obj->z = z << 8;
    obj->unk16 = 0;
    obj->unk12 = 0x100;
    obj->unk14 = 0x100;
    obj->unkA0 = 0;
    obj->unkA2 = 0;
    obj->unkA4 = 0;
    obj->unkA5 = 0;
    obj->velX = 0;
    obj->velY = 0;
    obj->velZ = 0;
    obj->accelX = 0;
    obj->accelY = 0;
    obj->accelZ = 0;
    obj->damping = 0x10;
    obj->unk18 = 0;
    obj->unk64 = 0;
    obj->frame = 0;
    obj->prevFrame |= 0xFFFF;
    obj->seqKey |= 0xFFFF;
    obj->seqOffset = 0;
    obj->seqStep = 0;
    obj->recIndex = 0;
    obj->unk2C = 0;
    obj->seqNextKey |= 0xFFFF;
    obj->unk10 = src->unk04;
    obj->unk11 = src->unk05;
    obj->unk30 = src->unk06;
    obj->unk2A = src->unk08;
    obj->unk38 = src->unk07;
    obj->unk28 = src->unk14;
    obj->flip = 0;
    obj->unk39 = 0;
    obj->unk3B = 0;
    obj->unk3A = src->unk0C;
    obj->animHold = 0;
    obj->unk74 = -1;
    obj->unk78 = 0;
    obj->unk7C = 0;
    obj->path = 0;
    obj->pathStep = -1;
    obj->unk88 = 0;
    obj->unk8C = 0;
    obj->unk8D = 0;
    obj->flags = 0;
    obj->unk90 = 0;
    obj->unk94 = 0;
    obj->unkB0 = 0;
    obj->unkB4 = 0;
    sub_08068574((struct Actor *)obj, obj->unk10 >> 1, obj->unk11, 0);
    sub_08068558((struct Actor *)obj, 0, 0, obj->unk10, obj->unk11);
    obj->unkB8 = 0;
    obj->unkBC = 0;
    AnimObjSetRecord((struct AnimObjPlayback *)obj, 0);
    obj->onFinish = 0;
}

