#include "global.h"

void sub_08035624(struct Unk346C0 *a, u32 type_arg, s32 delta_arg)
{
    u8 type;
    u8 type_copy;
    s32 delta;
    s32 value;
    struct Unk705DC *target;

    type = type_arg;
    type_copy = type;
    delta = (s8)delta_arg;
    value = a->unk00->unk00->unk22 + delta;
    if (type == 1)
        goto type_one;
    if (type > 1)
    {
        if (type_copy == 2)
            goto type_two;
        goto done;
    }
    if (type == 0)
        goto type_zero;
    goto done;

type_zero:
    a->unkD8 = value;
    target = a->unkD4;
    goto update;

type_one:
    a->unk1B4 = value;
    target = a->unk1B0;

update:
    if (target == 0)
        goto done;
    sub_08070468(target, (u16)value);
    goto done;

type_two:
    a->unk290 = value;
    target = a->unk28C;
    if (target == 0)
        goto done;
    sub_08070468(target, (u16)value);

done:
    return;
}
