#include "global.h"

// @ 0x08067f3c
// 58/92, compiled 96. Product lands in r3 (`muls r3, r2`) instead of r2, and the
// u16 countdown is `lsls/lsrs` rather than `subs r1,#1`. s32 counters and a
// mask-first flag test both scored worse.
s32 sub_08067F3C(void *a, u32 v)
{
    struct Unk67F3C *obj = a;
    struct Unk68014 *inner = obj->unk00;
    struct Unk68014Rec *rec = sub_08068014((struct Unk68014 **)obj, v);
    void *base = sub_08068884(inner);
    u16 n = rec->unk02;
    s32 sum = rec->unk04 * n;
    u16 head = rec->unk00;
    u16 *p;

    if ((s32)v >= (s32)inner->unk08)
        return 0;
    if (base != 0 && (obj->unk98 & 4) == 0 && n != 0)
    {
        p = (u16 *)base + head;
        do
        {
            sum += *p;
            p++;
            n--;
        } while (n != 0);
    }
    return sum;
}
