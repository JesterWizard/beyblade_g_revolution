#include "global.h"

// @ 0x0806bb38
void *sub_0806BB38(void *a, u32 idx)
{
    u8 bit;
    bit = *(u8 *)((u8 *)a + 6);
    return (u8 *)a + (idx << bit) + *(u32 *)((u8 *)a + 0x10);
}
