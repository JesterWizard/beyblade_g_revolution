#include "global.h"

// @ 0x0804745c
#include "global.h"

// @ 0x0804745c
void sub_0804745C(void)
{
    s32 i;
    u32 base;
    s32 off;

    if (*(void **)gUnk_03000630 != 0)
    {
        for (i = 0; i <= 0xF; i++)
        {
            base = *(u32 *)gUnk_03000630;
            off = i * 4;
            if (*(void **)(base + off) != 0)
            {
                sub_0806FE84(*(void **)(base + off));
                *(void **)(*(u32 *)gUnk_03000630 + off) = 0;
            }
        }
    }
    if (*(void **)gUnk_03000638 != 0)
    {
        sub_0806A434(*(void **)gUnk_03000638);
        *(void **)gUnk_03000638 = 0;
    }
    *(void **)gUnk_03000630 = 0;
}

