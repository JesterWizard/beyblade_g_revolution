#include "global.h"

// @ 0x0806171c

void TextDrawAlign(void *data, u32 index, u32 mode)
{
    s32 value;

    if (index >= gUnk_03000798->unk98)
        return;
    value = TextMeasureWidth(
        data,
        (void *)gUnk_03000798->unk8C,
        gUnk_03000798->unkA0,
        gUnk_03000798->unk9C);
    switch (mode)
    {
    case 0:
        gUnk_03000798->unk90 = index - ((u32)value >> 1);
        break;
    case 2:
        gUnk_03000798->unk90 = index;
        break;
    case 1:
        gUnk_03000798->unk90 = index - value;
        break;
    }
    TextDraw(data);
}

