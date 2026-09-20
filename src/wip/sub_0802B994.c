#include "global.h"

void *sub_0802B994(void)
{
    register u32 key asm("r3");
    register struct Unk7709C *r2 asm("r2");
    register u32 *r1 asm("r1");
    register u32 r0 asm("r0");

    key = gMainWorkPtr->unk1690->unk00;
    r2 = (struct Unk7709C *)0x0807709C;
    r0 = r2->unk04;
    if (r0 == 0)
        goto ret0;
    r1 = &r2->unk04;
loop:
    r0 = r2->unk00;
    if (r0 == key)
    {
        r0 = *r1;
        goto done;
    }
    r1 += 2;
    r2++;
    r0 = *r1;
    if (r0 != 0)
        goto loop;
ret0:
    r0 = 0;
done:
    return (void *)r0;
}
