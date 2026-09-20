#include "global.h"

// @ 0x08047594
#include "global.h"

// @ 0x08047594
void sub_08047594(void)
{
    s32 i;
    u32 base;
    s32 off;
    void *entry;

    if (*(void **)gUnk_03000630 != 0)
    {
        for (i = 0; i <= 0xF; i++)
        {
            base = *(u32 *)gUnk_03000630;
            off = i << 2;
            entry = *(void **)(base + off);
            *(u32 *)((u32)entry + 0x08) = 0xFFFFC000;
            *(u32 *)((u32)entry + 0x0C) = 0xFFFFC000;
        }
    }
}

