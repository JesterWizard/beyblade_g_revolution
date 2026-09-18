#include "global.h"

// @ 0x080361cc
void sub_080361CC(struct Unk36190 *src, struct Unk361CCDst *dst)
{
    s32 t;

    dst->unk48 = (s16)((s32)src->unk0C >> 8);
    dst->unk4A = (s16)((s32)src->unk10 >> 8);
    dst->unk4C = (s32)src->unk00;
    dst->unk50 = (s32)src->unk04;
    t = -(s32)src->unk08;
    dst->unk30 = t;
    dst->unk34 = t;
    dst->unk28 = -(s32)src->unk14;
}
