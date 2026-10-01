#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0807309c
void *StringAlloc(u32 size)
{
    void *buf = 0;
    struct BtlObj **table;
    struct BtlObj *obj;
    u32 i;

    if (gData_03004150 == 0)
        return 0;
    table = gData_03004150;

    for (i = 0; i < gData_03004154 && table[i] != 0; i++)
        ;
    if (i == gData_03004154)
        return 0;

    obj = HeapAlloc(size);
    table[i] = obj;
    if (obj == 0)
        return 0;

    buf = obj->next;
    MemClear(buf, size);
    gData_03004158++;
    return buf;
}

