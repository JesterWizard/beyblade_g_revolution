#include "global.h"

// @ 0x0807309c
void *sub_0807309C(u32 size)
{
    struct BtlObj **table;
    u8 count;
    u32 i;
    struct BtlObj **slot;
    struct BtlObj *obj;

    table = *(struct BtlObj ***)gBtlObjTable;
    if (table == 0)
        return 0;

    count = *(u8 *)gBtlObjTableCount;
    for (i = 0; i < count; i++)
    {
        if (table[i] == 0)
            break;
    }

    if (i == *(u8 *)gBtlObjTableCount)
        return 0;

    slot = &table[i];
    obj = sub_0806A3A4(size);
    *slot = obj;
    if (obj == 0)
        return 0;

    sub_08073184((u8 *)obj, size);
    (*(u8 *)gBtlObjLiveCount)++;
    return obj;
}
