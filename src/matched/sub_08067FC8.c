#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067fc8
#include "global.h"

u32 sub_08067FC8(void *a, u32 b)
{
    void *obj;
    u16 key;
    u32 total;
    struct Unk680CCRec *p;
    u32 i;
    struct Unk680CCRec *cursor;

    obj = a;
    key = (u16)b;
    total = 0;
    p = sub_08067F98(obj, key);
    if (p == 0)
        return 0;
    i = 0;
    if (total >= p->unk04)
        goto done;
    cursor = p;
    do
    {
        total += sub_08067F3C(obj, cursor->unk08);
        cursor = (struct Unk680CCRec *)((u16 *)cursor + 1);
        i++;
    } while (i < p->unk04);
done:
    return total;
}

