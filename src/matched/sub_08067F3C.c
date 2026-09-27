#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067f3c
/* match-compiler: old_agbcc */
// Sum `rec->unk02` halfwords from the animation's halfword table starting at
// `rec->unk00`, on top of the base value `rec->unk04 * rec->unk02`.
s32 AnimHalfwordSum(void *a, u32 v)
{
    struct Unk67F3C *obj = a;
    struct Unk68014 *inner;
    struct Unk68014Rec *rec;
    u16 *base;
    u16 *p;
    u32 n;
    s32 sum;
    u32 start;
    u32 i;

    inner = obj->unk00;
    rec = AnimRecAt(&obj->unk00, v);
    base = AnimHalfwordBase(inner);
    n = rec->unk02;
    sum = rec->unk04 * n;
    start = rec->unk00;
    if ((s32)v >= (s32)inner->unk08)
        return 0;
    if (base != 0 && !(obj->unk98 & 4) && n != 0)
    {
        p = &base[start];
        i = n;
        do
        {
            sum += *p++;
        } while (--i != 0);
    }
    return sum;
}

