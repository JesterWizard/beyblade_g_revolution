#include "global.h"

// @ 0x08060254
void sub_08060254(u32 a, u32 b, u32 c)
{
    sub_080601C4(a, b + ((gUnk_03000180.unk00 >> 4) & c));
}

