/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08041B74(void *a, void *b)
{
    s16 i;
    s16 count;
    struct Unk68574 **slot;

    i = 0;
    count = gData_03000504[0];
    if (count > 0)
    {
        for (; i < (s16)gData_03000504[0]; i++)
        {
            slot = &gData_03000480[i];
            if (*slot != NULL && (*slot)->unkD4 == a && (*slot)->unkD8 == b)
            {
                if ((*slot)->unkC8 != NULL)
                {
                    sub_08059D08((struct Unk59D08 *)(*slot)->unkC8);
                    (*slot)->unkC8 = NULL;
                }
                sub_08068808(*slot);
                (*slot)->unk04 = -0x4000;
                (*slot)->unk08 = -0x4000;
                *slot = gData_03000480[(s16)--gData_03000504[0]];
                gData_03000480[(s16)gData_03000504[0]] = NULL;
                return;
            }
        }
    }
}
