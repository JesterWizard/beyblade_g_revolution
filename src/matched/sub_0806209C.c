#include "global.h"

// @ 0x0806209c

void sub_0806209C(struct Unk62044 *a)
{
    s32 i;
    void *p;

    if (a == 0)
        return;
    if (a->unk0C != 0)
    {
        i = 0;
        do
        {
            p = a->unk0C[i];
            if (p == 0)
                break;
            sub_0806FE84(p);
            a->unk0C[i] = 0;
            i++;
        } while (i <= 0x7F);
    }
    a->unk24 = 0;
}

