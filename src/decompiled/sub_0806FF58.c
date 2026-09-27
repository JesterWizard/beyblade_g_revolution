#define sub_0806FF58 sub_0806FF58_old
#include "global.h"
#include "ram_map.h"
#undef sub_0806FF58

struct Unk6FF58Src
{
    u8 filler_00[6];
    u8 unk06;
    s8 unk07;
    u8 filler_08[4];
    u8 unk0C;
    u8 filler_0D[3];
    u32 unk10;
    u8 filler_14[8];
    u32 unk1C;
};

void sub_0806FF58(void *obj, void *srcArg, u32 x, u32 y, u8 e, u8 f, u8 g, u16 h)
{
    struct Unk705DC *dst = obj;
    struct Unk6FF58Src *src = srcArg;
    s8 pri;
    u8 shape;

    pri = src->unk07;
    shape = src->unk0C;
    dst->unk2C = src;
    dst->unk1C = g;
    dst->unk08 = x;
    dst->unk0C = y;
    dst->unk10 = ((pri & 3) << 14) | ((~shape & 1) << 13) | (((e & 3) << 10) | 0x1000) | ((pri & 0xC) << 28) | ((g & 3) << 28);
    dst->unk14 = (((shape >> 1) & 0xF) << 12) | ((f & 3) << 10);
    dst->unk28 = (u8 *)src + (src->unk1C != 0 ? src->unk1C : src->unk10);
    dst->unk16 = src->unk06;
    dst->unk18 = h;
    dst->unk1A = 0xFFFF;
    dst->unk1C = 0;
    dst->unk20 = 0;
    dst->unk24 = -1;
    dst->unk1E = 0;
}

