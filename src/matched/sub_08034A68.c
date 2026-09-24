#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08034a68
/* match-compiler: old_agbcc */
#include "global.h"

void sub_08034A68(struct Unk346C0 *a, u32 b)
{
    a->unk310 = 0;
    if (a->unk314 == 1)
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

