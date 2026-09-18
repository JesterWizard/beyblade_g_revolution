#include "global.h"

// @ 0x08041348
void sub_08041348(struct Unk41348 *a)
{
    struct Unk41348Inner *inner;

    inner = a->unk248;
    a->unk322 = 2;
    a->unk31C = 0;
    a->unk320 = inner->unk4C;
    a->unk31E = inner->unk4A;
    a->unk2D7 = 1;
}
