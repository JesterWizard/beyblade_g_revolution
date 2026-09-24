#include "global.h"

// @ 0x08030f00
void sub_08030F00(struct Unk30F00 *a, struct Unk30F00Src *b)
{
    struct Unk30F00Mid *mid;
    struct Unk30F00Inner *inner;
    struct Unk705DC *leaf;
    u32 t;

    if (a == 0)
        return;
    mid = b->unk00;
    inner = mid->unk00;
    if (inner == 0)
        return;
    a->unk08 = inner->unk08;
    t = 0xFFFFF000;
    a->unk0C = inner->unk0C + t;
    leaf = inner->unk30;
    if (leaf == 0)
        return;
    sub_08070354((struct Unk70354 *)a, leaf->unk14, leaf->unk16, 0);
}

