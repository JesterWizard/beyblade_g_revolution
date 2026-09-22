#include "global.h"

// @ 0x0807309c
void *sub_0807309C(u32 size)
{
    struct BtlObj **table;
    u32 i;
    struct BtlObj *obj;
    void *v;

    table = *(struct BtlObj ***)gBtlObjTable;
    if (table == 0)
        return 0;

    for (i = 0; i < *(u8 *)gBtlObjTableCount && table[i] != 0; i++)
        ;

    if (i == *(u8 *)gBtlObjTableCount)
        return 0;

    obj = sub_0806A3A4(size);
    table[i] = obj;
    if (obj == 0)
        return 0;

    v = obj->next;
    sub_08073184(v, size);
    (*(u8 *)gBtlObjLiveCount)++;
    return v;
}
