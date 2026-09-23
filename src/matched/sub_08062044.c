#include "global.h"

// @ 0x08062044
void sub_08062044(struct Unk62044 *a)
{
    if (a != 0)
    {
        sub_0806209C(a);
        if (a->unk00 != 0)
        {
            HeapFree(a->unk00);
            a->unk00 = 0;
        }
        a->unk0C = 0;
    }
}

