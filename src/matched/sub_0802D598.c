#include "global.h"

// @ 0x0802d598

void sub_0802D598(void)
{
    struct Sprite *q;

    gUnk_0300026C->markerShown = 0;
    q = gUnk_0300026C->marker;
    q->unk08 = 0xFFFFC000;
    q->unk0C = 0xFFFFC000;
}

