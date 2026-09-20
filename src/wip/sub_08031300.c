#include "global.h"

// @ 0x08031300
void sub_08031300(struct Unk312EC *a)
{
    s32 n;
    struct Unk705DC *b;
    u32 id;

    if (a->unk08 != 0)
    {
        n = a->unk04;
        if (n >= 0)
        {
            n--;
            a->unk04 = n;
            b = a->unk0C;
            if (b != 0)
            {
                id = b->unk14 >> 0xC;
                n &= 5;
                if (n == 0)
                {
                    if (id == a->unk01)
                        id = a->unk00;
                    else
                        id = a->unk01;
                    sub_080705DC(b, (u8)id);
                }
            }
        }
        else
        {
            sub_080312D8(a);
        }
    }
}
