#include "global.h"

// @ 0x08070604
void sub_08070604(struct Unk70604 *dst, struct Unk70604Src *src, s32 unk20, s16 x, s16 y, u16 unk0C, u16 unk08)
{
    register u32 val;
    u8 *p;

    dst->unk00 = (s32)x << 8;
    dst->unk04 = (s32)y << 8;
    dst->unk0C = unk0C;
    dst->unk0A = 0;
    dst->unk1C = 0;
    dst->unk18 = 0;
    dst->unk14 = 0;
    dst->unk20 = unk20;
    dst->unk24 = src;
    dst->unk08 = unk08;
    dst->unk2C = 0;
    dst->unk0E = 0;
    dst->unk10 = 0x100;
    dst->unk12 = 0x100;
    dst->unk0F = 0;
    dst->unk2B = 0;
    dst->unk28 = 5;

    p = &dst->unk29;
    *p = 0;
    val = src->unk05;
    val += 4;
    p += 1;
    *(s8 *)p = val;
}

