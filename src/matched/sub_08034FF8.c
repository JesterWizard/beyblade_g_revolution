#include "global.h"

// @ 0x08034ff8
void sub_08034FF8(struct Unk34FF8 *a, u32 b, u32 c)
{
    sub_08035878(&a->unk08, b, (u32)a, c);
    a->unk18 = 1;
    a->unk19 = 0;
}

