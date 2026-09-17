#include "global.h"

// @ 0x0806bb38
void *sub_0806BB38(struct Unk6BB38 *a, u32 idx)
{
    u8 bit;

    bit = a->unk06;
    return (u8 *)a + (idx << bit) + a->unk10;
}
