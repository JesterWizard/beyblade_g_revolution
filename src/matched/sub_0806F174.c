#include "global.h"

// @ 0x0806f174
void sub_0806F174(struct Unk6F174 *a, void *b)
{
    a->unk224 = b;
    if (a->unk348 == 0)
        sub_0806F05C(a);
    else
        _08073C4C(b, a, (u32)a, a->unk348);
}

