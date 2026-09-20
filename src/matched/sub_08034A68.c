#include "global.h"

// @ 0x08034a68
#include "global.h"

void sub_08034A68(struct Unk346C0 *a, u32 b)
{
    register u8 status asm("r1");

    a->unk310 = 0;
    status = a->unk314;
    if (status == 1)
    {
        a->unk2F8 = 0x3C;
        a->unk314 = 0;
    }
    a->unk311 = 0;
    a->unk30F = 0;
    a->unk2CC = 5;
    sub_08035238((struct Unk35258 *)a);
    sub_080347E4(a);
    if (a->unk30C == 1)
    {
        sub_08034FDC((struct Unk34FF8 *)a, b);
        sub_08035884(&a->unk08);
    }
}

