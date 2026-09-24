#include "global.h"

// @ 0x08070604
/* match-compiler: old_agbcc */
void sub_08070604(struct Unk70604 *dst, struct Unk70604Src *src, s32 unk20, s16 x, s16 y, u16 unk0C, u16 unk08)
{
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
    dst->unk29 = 0;
    dst->unk2A = (s8)(src->unk05 + 4);
}
