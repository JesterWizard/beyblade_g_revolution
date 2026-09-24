#include "global.h"

// @ 0x080302a8
void sub_080302A8(struct Unk302A8 *a, struct Unk302A8Src *b, struct Unk302A8 *dst)
{
    struct Unk302A8Inner *inner;
    s32 half;
    s32 neg;

    neg = -b->unk08;
    inner = a->unk00;
    half = a->unk14 >> 2;
    dst->unk08 = inner->unk08 + half + 0x400;
    dst->unk0C = inner->unk0C + half + 0x400;
    neg = (u32)(neg << 8) >> 16;
    sub_08070354((struct Unk70354 *)dst, neg, neg, 0);
}
