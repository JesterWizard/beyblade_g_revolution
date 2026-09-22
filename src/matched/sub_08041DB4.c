#include "global.h"

// @ 0x08041db4
void *sub_08041DB4(u32 a, u32 b)
{
    s16 i;
    s16 count;
    struct Unk68574 **pool;
    struct Unk68574 *p;

    i = 0;
    count = *(s16 *)gUnk_03000504;
    if (count > 0 && i < count)
    {
        pool = (struct Unk68574 **)gUnk_03000480;
        do
        {
            p = pool[i];
            if (p != 0 && p->unkD4 == (void *)a && p->unkD8 == (void *)b)
                return p;
            i++;
        } while (i < count);
    }
    return 0;
}

