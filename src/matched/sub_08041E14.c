#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08041e14
s32 sub_08041E14(void *a, void *b)
{
    s16 i;
    s16 count;
    struct Unk68574 *obj;

    i = 0;
    count = gData_03000504[0];
    if (count > 0)
    {
        for (; i < count; i++)
        {
            obj = gData_03000480[i];
            if (obj != NULL && obj->unkD4 == a && obj->unkD8 == b)
            {
                if (obj->unkC8 == NULL || obj->unkC8->unk10 == NULL || obj->unkC8->unk10->unk10 == NULL)
                    return 0;
                return 1;
            }
        }
    }
    return 0;
}


