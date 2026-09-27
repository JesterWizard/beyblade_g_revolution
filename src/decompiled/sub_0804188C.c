#include "global.h"
#include "ram_map.h"

void sub_0804188C(void)
{
    s16 i;
    struct Unk68574 **slot;
    s32 value;
    u32 color;

    i = 0;
    if (gData_03000504 > 0)
    {
        sub_08062B9C(3, 0x0F);
        for (; i < gData_03000504;)
        {
            slot = &gData_03000480[i];
            sub_08068418(*slot);
            if ((*slot)->unkB8 != NULL)
            {
                if ((*slot)->unkD8 == (void *)1)
                {
                    (*slot)->unkBC = 0xFFFF;
                    sub_08070468((struct Unk6FDB4 *)(*slot)->unkB8, (*slot)->unkBC);
                }
                else
                {
                    (*slot)->unkBC = ~((s32)(*slot)->unk08 >> 8);
                    sub_08070468((struct Unk6FDB4 *)(*slot)->unkB8, (*slot)->unkBC);
                }
                if (gData_03000480[i]->unkD8 == NULL)
                    value = sub_08062AF8((void *)0x080775CC, gData_03000480[i]->unkD4);
                else
                    value = sub_08062AF8((void *)0x080779A8, gData_03000480[i]->unkD4);
                color = (u16)(((value << 24) >> 8) >> 16);
                gData_03000480[i]->unk3A = (color << 1) | 1;
            }
            sub_08067CE8(gData_03000480[i++], 0);
        }
    }

}
