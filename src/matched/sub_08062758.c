#include "global.h"

// @ 0x08062758
void sub_08062758(struct Unk62728 *a, u32 b)
{
    u32 i;
    void **p;
    struct Unk62790Obj *obj;

    i = 0;
    p = (void **)a->unk04;
    do
    {
        obj = *p;
        if (obj != 0)
        {
            sub_08062790(b, obj, obj->unkCC, obj->unkD0, i);
        }
        p++;
        i++;
    } while (i < a->unk08);
}

