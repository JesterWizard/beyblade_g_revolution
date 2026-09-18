#include "global.h"

// @ 0x080703fc
void sub_080703FC(struct Unk703FC *a, u16 b, u16 c)
{
    if (a->unk30 != 0)
        sub_08070354(a, b, c, a->unk30->unk18);
    else
        sub_08070354(a, b, c, 0);
}

