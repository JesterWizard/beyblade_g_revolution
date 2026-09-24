#include "global.h"

// @ 0x08041b74
void sub_08041B74(u32 a, u32 b)
{
    s16 i;
    s16 count;
    struct Unk68574 **pool;
    struct Unk68574 *p;
    s16 newCount;

    i = 0;
    count = *(s16 *)gUnk_03000504;
    if (count > 0 && i < count)
    {
        pool = (struct Unk68574 **)gUnk_03000480;
        do
        {
            p = pool[i];
            if (p != 0 && p->unkD4 == (void *)a && p->unkD8 == (void *)b)
            {
                if (p->unkC8 != 0)
                {
                    sub_08059D08((struct Unk59D08 *)p->unkC8);
                    p->unkC8 = 0;
                }
                sub_08068808(p);
                p->unk04 = 0xFFFFC000;
                p->unk08 = 0xFFFFC000;
                newCount = count - 1;
                *(s16 *)gUnk_03000504 = newCount;
                pool[i] = pool[newCount];
                pool[newCount] = 0;
                break;
            }
            i++;
        } while (i < count);
    }
}
