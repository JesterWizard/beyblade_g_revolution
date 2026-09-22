#include "global.h"

void sub_0803559C(void *obj, u32 b, u32 value)
{
    struct Unk35258 *base;
    struct Unk680CC *target;
    u8 type;

    base = obj;
    type = b;
    if (type == 1)
        goto type_one;
    if (type > 1)
    {
        if (type == 2)
            goto type_two;
        goto done;
    }
    if (type == 0)
        goto type_zero;
    goto done;

type_zero:
    if (base->unk1C.unk1A == value)
        goto done;
    target = (struct Unk680CC *)&base->unk1C;
    goto update;

type_one:
    if (base->unkF8.unk1A == value)
        goto done;
    target = (struct Unk680CC *)&base->unkF8;

update:
    value = (u16)value;
    sub_08068020(target, value, value);
    goto done;

type_two:
    if (base->unk1D4.unk1A == value)
        goto done;
    target = (struct Unk680CC *)&base->unk1D4;
    value = (u16)value;
    sub_08068020(target, value, value);

done:
    return;
}
