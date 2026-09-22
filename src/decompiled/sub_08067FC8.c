#include "global.h"

// @ 0x08067fc8
// 43/74 same-size. Retail: `r8 = 0` (total) is set BEFORE the sub_08067F98 call,
// the entry check compares r8 (total, i.e. a known zero) against the u16 count,
// and the loop keeps p in r5, a in r7, the element cursor in r4, i in r6.
// Hoisting `total = 0` above the call in C makes agbcc emit a different
// prologue/register set (26/74, size mismatch), so the initialiser order that
// scores best is the one below. struct Unk680CCRec gained unk04 (element count)
// and unk06 for this function.
// Role: sum sub_08067F3C over a keyed record's u16 list.
u32 sub_08067FC8(void *a, u32 b)
{
    struct Unk680CCRec *p = sub_08067F98((struct Unk680CC *)a, (u16)b);
    u32 total = 0;
    u32 i;
    u16 *e;

    if (p == 0)
        return 0;
    e = &p->unk08;
    for (i = 0; i < p->unk04; i++)
        total += sub_08067F3C(a, e[i]);
    return total;
}
