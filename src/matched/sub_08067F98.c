#include "global.h"

// @ 0x08067f98
/* match-compiler: old_agbcc */
struct Unk680CCRec *sub_08067F98(struct Unk680CC *a, u32 key)
{
    u32 r1;
    u8 *r2;
    u32 r3;
    u32 r4;
    u32 r0;

    r1 = key;
    r1 <<= 16;
    r3 = r1 >> 16;
    r2 = (u8 *)a->unk00;
    r1 = ((struct Unk68014 *)r2)->unk18;
    r2 += r1;
    r1 = 0;
    r0 = a->unk28;
    if (r1 >= r0)
        goto notfound;
loop:
    r4 = *(u16 *)r2;
    if (r4 != r3)
        goto next;
    r0 = (u32)r2;
    goto done;
next:
    r4 = *(u16 *)(r2 + 2);
    r2 = (u8 *)(r4 + (u32)r2);
    r1++;
    if (r1 < r0)
        goto loop;
notfound:
    r0 = 0;
done:
    return (struct Unk680CCRec *)r0;
}


