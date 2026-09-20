#include "global.h"

// @ 0x0804495c
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_0804495C(void)
{
    register u32 r1 asm("r1");
    register s32 r0 asm("r0");
    register u16 *src asm("r1");
    register u16 *dst asm("r3");
    register s32 n asm("r2");
    register u16 tmp asm("r0");

    r1 = 0x08094E00;
    asm("" : "+r"(r1));
    r0 = gMainWorkPtr->unk181F;
    r0 <<= 2;
    r0 = r0 + r1;
    src = *(u16 **)r0;
    dst = (u16 *)0x050001C0;
    n = 0x1F;
    do
    {
        tmp = *src;
        *dst = tmp;
        src++;
        dst++;
        n--;
    } while (n >= 0);
}

