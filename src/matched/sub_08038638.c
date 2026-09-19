#include "global.h"

// @ 0x08038638
void sub_08038638(u16 a)
{
    u16 raw = (u16)gUnk_030003CC->unk22[a];

    if (gUnk_030003CC->unk22[a] > 0)
        gUnk_030003CC->unk22[a] = raw - 1;

    if (gUnk_030003CC->unk22[a] == 0)
        sub_080385DC(a, a);
}

