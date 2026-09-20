#include "global.h"

// @ 0x0806225c
#include "global.h"

void sub_0806225C(struct Unk62634 *a)
{
    struct Unk705DC *target;

    if (a == 0)
        return;
    a->unk24 += a->unk30;
    a->unk28 += a->unk34;
    a->unk30 += a->unk38;
    a->unk34 += a->unk3C;
    if (a->unk30 != 0)
    {
        if (a->unk30 > 0)
            a->unk30 -= a->unk40;
        if (a->unk30 < 0)
            a->unk30 += a->unk40;
    }
    if (a->unk34 != 0)
    {
        if (a->unk34 > 0)
            a->unk34 -= a->unk40;
        if (a->unk34 < 0)
            a->unk34 += a->unk40;
    }
    if (a->unk04 != 0)
    {
        target = a->unk08;
        if (target != 0)
        {
            target->unk08 = a->unk24 - a->unk04->unk0C;
            target->unk0C = a->unk28 - a->unk04->unk10;
            sub_080705DC(target, a->unk60);
        }
    }
    else
    {
        target = a->unk08;
        if (target != 0)
        {
            target->unk08 = a->unk24;
            target->unk0C = a->unk28;
            sub_080705DC(target, a->unk60);
        }
    }
    if (a->unk00 != 0)
        sub_08062358(a);
    if (a->unk18 != 0)
        sub_08062640((struct Unk62634 *)a);
}

