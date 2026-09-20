#include "global.h"

// @ 0x0806b3e8
void sub_0806B3E8(struct Unk6B3E8 *arg0)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    register u32 r2 asm("r2");
    register s32 r4 asm("r4");
    register struct Unk6B3E8Item *r5 asm("r5");
    register const u8 *r6 asm("r6");

    r4 = arg0->unk04;
    r6 = arg0->unk10;
    r5 = arg0->unk00;
    goto check;
loop:
    if (r1 == 0x20)
        goto check;
    r0 = 0x080BB748;
    asm("" : "+r"(r0));
    r0 = r1 + r0;
    r2 = *(u8 *)r0;
    r0 = (u32)r5;
    r1 = 0;
    sub_0806833C((void *)r0, (s32)r1, (u16)r2);
    r0 = 1;
    r0 = -r0;
    r5->unk70 = (s32)r0;
    r5++;
    r4--;
check:
    if (r4 == 0)
        goto fill;
    r1 = *r6;
    r6++;
    if (r1 != 0)
        goto loop;
fill:
    r0 = (u32)r4;
    r4--;
    if (r0 == 0)
        goto done;
    r1 = 0;
fillloop:
    r5->unk70 = (s32)r1;
    r5++;
    r0 = (u32)r4;
    r4--;
    if (r0 != 0)
        goto fillloop;
done:
    return;
}

