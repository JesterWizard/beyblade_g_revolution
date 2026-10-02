#include "global.h"

// @ 0x0802d898
void sub_0802D898(s32 a, s32 b)
{
    struct StatusHud *p;
    struct Sprite *q;

    p = gUnk_0300026C;
    q = p->marker;
    if (q != 0)
    {
        q->unk08 = a + 0xFFFFF800;
        q->unk0C = b + 0xFFFFF800;
        p->markerShown = 1;
    }
}

