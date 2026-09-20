#include "global.h"

// @ 0x08041858
void sub_08041858(void)
{
    register void **slot asm("r4");
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");

    sub_08041980();
    slot = (void **)gUnk_03000508;
    if (*slot != 0)
    {
        sub_0806A434(*slot);
        *slot = 0;
    }
    r0 = gUnk_03000534;
    r1 = 0;
    *(s32 *)r0 = r1;
    asm("" : "+r"(r0), "+r"(r1) : : "memory");
    r0 = gUnk_03000504;
    asm("" : "+r"(r0));
    *(u16 *)r0 = (u16)r1;
}

