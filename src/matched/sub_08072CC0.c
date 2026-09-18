#include "global.h"

// @ 0x08072cc0
void sub_08072CC0(struct Unk72CC0 *a)
{
    if (a->unk10 != 0)
    {
        sub_0806A434(a->unk10);
        a->unk10 = 0;
    }
}

