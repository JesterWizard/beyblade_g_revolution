#include "global.h"

// @ 0x0806639c
void *sub_0806639C(void)
{
    u32 tmp[2];
    void **base;
    s32 idx;

    tmp[0] = 0x080BA1A8;
    base = (void **)tmp[0];
    idx = (s8)*((u8 *)gUnk_03000964);
    idx <<= 2;
    return *((void **)(((u8 *)((void **)tmp[0])) + idx));
}

