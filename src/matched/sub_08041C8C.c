#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08041c8c
/* match-compiler: old_agbcc */
void sub_08041C8C(void *a, void *b, u32 *src)
{
    s16 i;
    struct Actor *obj;
    struct Unk41E14Node *node;
    struct Unk41C8CDst *dst;

    i = 0;
    if (gData_03000504 > 0)
    {
        for (; i < gData_03000504; i++)
        {
            obj = gData_03000480[i];
            if (obj != NULL && obj->unkD4 == a && obj->unkD8 == b)
            {
                node = obj->unkC8;
                if (node == NULL || node->unk10 == NULL)
                    return;
                node->unk10->unk10 = (struct Unk41E14Node *)src;
                dst = node->unk30;
                dst->unk00 = src[0];
                dst->unk06 = src[1];
                dst->unk04 = 0;
                return;
            }
        }
    }
}


