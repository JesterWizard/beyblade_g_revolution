#include "global.h"

void sub_080610A8(
    struct Unk610A8 *base,
    u8 *text,
    u32 index,
    u32 mode)
{
    s32 value;

    if (base == 0 || index >= base->unk98)
        return;
    value = TextMeasureWidth(text, base->unk8C, base->unkA0, base->unk9C);
    switch (mode)
    {
    case 0:
        base->unk90 = index - ((u32)value >> 1);
        break;
    case 2:
        base->unk90 = index;
        break;
    case 1:
        base->unk90 = index - value;
        break;
    }
    sub_0806105C(base, text);
}
