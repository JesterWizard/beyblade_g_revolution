#include "global.h"

// @ 0x08041858
void sub_08041858(void)
{
    s32 *p1;
    register u16 *p2 asm("r0");

    sub_08041980();
    if (*(void **)gUnk_03000508 != 0)
    {
        sub_0806A434(*(void **)gUnk_03000508);
        *(void **)gUnk_03000508 = 0;
    }
    p1 = (s32 *)gUnk_03000534;
    *p1 = 0;
    p2 = (u16 *)gUnk_03000504;
    *p2 = 0;
}
