#include "global.h"

// @ 0x0806d958
void sub_0806D958(struct Unk6D958 *a)
{
    struct Unk6D958Inner *inner;

    inner = a->unk90;
    if (inner != 0 && inner->unk04 != 0)
        _08073C4C(a, a->unk80, (u32)a->unk84, inner->unk04);
    a->unk80 = 0;
    a->unk84 = -1;
    a->unk88 = 0;
}

