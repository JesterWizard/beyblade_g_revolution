#include "global.h"

// @ 0x0807309c
void *BtlObjTableAdd(u32 size)
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

    obj = BtlObjAlloc(size);
    table[i] = obj;
    if (obj == 0)
        return 0;

    v = obj->next;
    MemClear(v, size);
    (*(u8 *)gBtlObjLiveCount)++;
    return v;
}
