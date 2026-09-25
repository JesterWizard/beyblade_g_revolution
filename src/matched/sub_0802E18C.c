#include "global.h"

// @ 0x0802e18c
void HudWriteDigits(struct Unk310F0b *tens, struct Unk310F0b *ones, s32 value)
{
    if (value <= 99)
    {
        tens->shown = Div(value, 10);
        ones->shown = DivRemainder(value, 10);
    }
}

