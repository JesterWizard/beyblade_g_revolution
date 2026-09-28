#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067bb8
/* match-compiler: old_agbcc */
// Construct an animated object from its template: position (x, y, z in pixels,
// stored 24.8), defaults for every state field, then frame/palette setup.
void AnimObjCreate(struct Unk67BB8 *obj, struct Unk67BB8Source *src, s32 arg2, s32 x, s32 y, s32 z, s32 arg6)
{
    obj->unk00 = src;
    obj->unk58 = gUnk_03000180.unk00;
    obj->unk3C = arg2;
    obj->unk70 = arg6;
    obj->unk04 = x << 8;
    obj->unk08 = y << 8;
    obj->unk0C = z << 8;
    obj->unk16 = 0;
    obj->unk12 = 0x100;
    obj->unk14 = 0x100;
    obj->unkA0 = 0;
    obj->unkA2 = 0;
    obj->unkA4 = 0;
    obj->unkA5 = 0;
    obj->unk40 = 0;
    obj->unk44 = 0;
    obj->unk48 = 0;
    obj->unk4C = 0;
    obj->unk50 = 0;
    obj->unk54 = 0;
    obj->unk68 = 0x10;
    obj->unk18 = 0;
    obj->unk64 = 0;
    obj->unk22 = 0;
    obj->unk60 |= 0xFFFF;
    obj->unk1A |= 0xFFFF;
    obj->unk1C = 0;
    obj->unk1E = 0;
    obj->unk20 = 0;
    obj->unk2C = 0;
    obj->unk2E |= 0xFFFF;
    obj->unk10 = src->unk04;
    obj->unk11 = src->unk05;
    obj->unk30 = src->unk06;
    obj->unk2A = src->unk08;
    obj->unk38 = src->unk07;
    obj->unk28 = src->unk14;
    obj->unk31 = 0;
    obj->unk39 = 0;
    obj->unk3B = 0;
    obj->unk3A = src->unk0C;
    obj->unk6C = 0;
    obj->unk74 = -1;
    obj->unk78 = 0;
    obj->unk7C = 0;
    obj->unk80 = 0;
    obj->unk84 = -1;
    obj->unk88 = 0;
    obj->unk8C = 0;
    obj->unk8D = 0;
    obj->unk98 = 0;
    obj->unk90 = 0;
    obj->unk94 = 0;
    obj->unkB0 = 0;
    obj->unkB4 = 0;
    sub_08068574((struct Unk68574 *)obj, obj->unk10 >> 1, obj->unk11, 0);
    sub_08068558((struct Unk68574 *)obj, 0, 0, obj->unk10, obj->unk11);
    obj->unkB8 = 0;
    obj->unkBC = 0;
    sub_08068180((struct Unk68598 *)obj, 0);
    obj->unkC0 = 0;
}

