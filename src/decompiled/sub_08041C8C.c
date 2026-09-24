#include "global.h"

// @ 0x08041c8c
void sub_08041C8C(u32 a, u32 b, u32 c)
{
    s16 i;
    s16 count;
    struct Unk68574 **pool;
    struct Unk68574 *p;
    struct Unk41E14Node *node;
    u32 *src;
    struct Unk41C8CDst *dst;

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
                node = p->unkC8;
                if (node == 0)
                    break;
                if (node->unk10 == 0)
                    break;
                src = (u32 *)c;
                node->unk10->unk10 = (struct Unk41E14Node *)c;
                dst = node->unk30;
                dst->unk00 = (u8)src[0];
                dst->unk06 = (u16)src[1];
                dst->unk04 = 0;
                break;
            }
            i++;
        } while (i < count);
    }
}
