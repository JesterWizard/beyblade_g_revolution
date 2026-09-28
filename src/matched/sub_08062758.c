#include "global.h"

// @ 0x08062758
void sub_08062758(struct Unk62728 *a, struct Actor *b)
{
    u32 i;
    void **p;
    struct Actor *obj;

    i = 0;
    p = (void **)a->unk04;
    do
    {
        obj = *p;
        if (obj != 0)
        {
            ProximityTriggerCheck(b, obj, obj->unkCC, obj->unkD0, i);
        }
        p++;
        i++;
    } while (i < a->unk08);
}

