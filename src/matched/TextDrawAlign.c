#include "global.h"

// @ 0x0806171c

void TextDrawAlign(void *data, u32 index, u32 mode)
{
    s32 value;

    if (index >= gUnk_03000798->width)
        return;
    value = TextMeasureWidth(
        data,
        (void *)gUnk_03000798->widthTable,
        gUnk_03000798->glyphWidth,
        gUnk_03000798->spacing);
    switch (mode)
    {
    case 0:
        gUnk_03000798->penX = index - ((u32)value >> 1);
        break;
    case 2:
        gUnk_03000798->penX = index;
        break;
    case 1:
        gUnk_03000798->penX = index - value;
        break;
    }
    TextDraw(data);
}

