#include "global.h"

s32 sub_08041E14(void *a, void *b)
{
    register void *a_ptr asm("r5");
    register void *b_ptr asm("r4");
    register s32 i asm("r1");
    register s32 count asm("r3");
    register struct Unk68574 **entries asm("r6");
    struct Unk68574 *obj;
    struct Unk41E14Node *node;

    a_ptr = a;
    b_ptr = b;
    i = 0;
    count = *(s16 *)gUnk_03000504;
    if (count <= 0 || i >= count)
        return 0;
    entries = (struct Unk68574 **)gUnk_03000480;
    while (i < count)
    {
        obj = entries[i];
        if (obj != 0)
        {
            if (obj->unkD4 == a_ptr && obj->unkD8 == b_ptr)
            {
                node = obj->unkC8;
                if (node == 0 || node->unk10 == 0 || node->unk10->unk10 == 0)
                    return 0;
                return 1;
            }
        }
        i++;
    }
    return 0;
}
