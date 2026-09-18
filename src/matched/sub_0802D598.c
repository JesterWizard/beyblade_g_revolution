#include "global.h"

// @ 0x0802d598
void sub_0802D598(void)
{
    struct Unk026C *p;
    struct Unk705DC *q;

    p = gUnk_0300026C;
    p->unk00 = 0;
    q = p->unk08;
    q->unk08 = 0xFFFFC000;
    q->unk0C = 0xFFFFC000;
}

