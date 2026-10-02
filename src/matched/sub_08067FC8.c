#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067fc8
#include "global.h"

u32 AnimDurationForKey(void *a, u32 b)
{
    void *obj;
    u16 key;
    u32 total;
    struct AnimSeqEntry *p;
    u32 i;
    struct AnimSeqEntry *cursor;

    obj = a;
    key = (u16)b;
    total = 0;
    p = sub_08067F98(obj, key);
    if (p == 0)
        return 0;
    i = 0;
    if (total >= p->stepCount)
        goto done;
    cursor = p;
    do
    {
        total += AnimHalfwordSum(obj, cursor->firstRecord);
        cursor = (struct AnimSeqEntry *)((u16 *)cursor + 1);
        i++;
    } while (i < p->stepCount);
done:
    return total;
}

