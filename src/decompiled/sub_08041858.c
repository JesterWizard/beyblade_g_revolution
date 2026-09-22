#include "global.h"

// @ 0x08041858
void sub_08041858(void)
{
    void **slot;
    u32 r0;
    u32 r1;

    sub_08041980();
    slot = (void **)gUnk_03000508;
    if (*slot != 0)
    {
        BtlObjFree(*slot);
        *slot = 0;
    }
    r0 = gUnk_03000534;
    r1 = 0;
    *(s32 *)r0 = r1;
r0 = gUnk_03000504;
*(u16 *)r0 = (u16)r1;
}

