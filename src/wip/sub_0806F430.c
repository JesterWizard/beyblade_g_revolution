#include "global.h"

// @ 0x0806f430
u32 sub_0806F430(void)
{
    struct Unk4084 *p;
    u32 tmp[1];
    u32 flags;
    u32 bit;
    u32 otherBit;

    tmp[0] = gUnk_03004084;
    p = *(struct Unk4084 **)tmp[0];
    otherBit = 0x10;
    flags = p->unk14;
    bit = 8;
    bit &= flags;
    if (bit != 0)
        return 1;
    flags &= otherBit;
    if (flags != 0)
        return 0;
    sub_08067B98((void *)0x083D2030);
    return 0;
}

