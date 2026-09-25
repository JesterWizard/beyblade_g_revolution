#include "global.h"

/* match-compiler: old_agbcc */
// @ 0x08067f3c
// 61/92 same_size. Remaining DIFF is muls operand regs (retail muls r2,r3;
// compiled muls r3,r2) after ldrh of unk02/unk04. Permuter 75/92 with broken
// while(rec->unk02) keeps muls matched but loop wrong.
s32 sub_08067F3C(void *a, u32 v)
{
    struct Unk67F3C *obj;
    struct Unk68014 *inner;
    struct Unk68014Rec *rec;
    void *base;
    u32 n;
    s32 sum;
    u32 head;
    u16 *p;

    obj = a;
    inner = obj->unk00;
    rec = sub_08068014((struct Unk68014 **)obj, v);
    base = sub_08068884(inner);
    n = rec->unk02;
    sum = rec->unk04;
    sum *= n;
    head = rec->unk00;
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
