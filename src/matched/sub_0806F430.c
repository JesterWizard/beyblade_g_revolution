#include "global.h"

// @ 0x0806f430
u32 sub_0806F430(void)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    struct Unk4084 *p;
    u32 tmp[1];

    tmp[0] = gUnk_03004084;
    p = *(struct Unk4084 **)tmp[0];
    r1 = p->unk14;
    r0 = 8;
    r0 &= r1;
    if (r0 != 0)
        return 1;
    r0 = 0x10;
    r1 &= r0;
    if (r1 != 0)
        return 0;
    sub_08067B98((void *)0x083D2030);
    return 0;
}
