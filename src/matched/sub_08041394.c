#include "global.h"

// @ 0x08041394
void sub_08041394(struct Unk41394 *a)
{
    s32 i;
    void *q;

    i = 0;
    do
    {
        q = a->unk220[i];
        if (q != 0)
        {
            BtlObjFree(q);
            a->unk220[i] = 0;
        }
        i++;
    } while (i <= 7);
}

