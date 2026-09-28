#include "global.h"

// @ 0x08060254
void SfxPlayVariant(u32 a, u32 b, u32 c)
{
    SfxPlayInSlot(a, b + ((gUnk_03000180.unk00 >> 4) & c));
}

