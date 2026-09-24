#include "global.h"

// @ 0x08041b74
void sub_08041B74(u32 a, u32 b)
{
    s16 i;
    s32 idxHi;
    s16 count;
    struct Unk68574 **pool;
    struct Unk68574 **slot;
    struct Unk68574 *p;
    u16 *countAddr;

    i = 0;
    countAddr = (u16 *)gUnk_03000504;
    count = *(s16 *)countAddr;
    if (count <= 0)
        return;
    if (i >= count)
        return;
    pool = (struct Unk68574 **)gUnk_03000480;
    while (i < count)
    {
        idxHi = (s32)i << 16;
        slot = &pool[i];
        p = *slot;
        if (p != 0 && p->unkD4 == (void *)a && p->unkD8 == (void *)b)
        {
            if (p->unkC8 != 0)
            {
                sub_08059D08((struct Unk59D08 *)p->unkC8);
                (*slot)->unkC8 = 0;
            }
            sub_08068808(*slot);
            p = *slot;
            p->unk04 = 0xFFFFC000;
            p->unk08 = 0xFFFFC000;
            count = *(s16 *)countAddr - 1;
            *(s16 *)countAddr = count;
            *slot = pool[count];
            pool[count] = 0;
            return;
        }
        idxHi += 0x10000;
        i = (s16)(idxHi >> 16);
    }
}
