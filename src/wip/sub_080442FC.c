#include "global.h"

void sub_080442FC(
    struct Unk442FC *a_arg,
    struct Unk442FCInput *b,
    u32 c,
    u32 d)
{
    register struct Unk442FC *a asm("r5");
    register u16 index asm("r4");
    s32 *coords;

    a = a_arg;
    index = 0;
    if (b != 0)
    {
        index = b->unk16;
        gMainWorkPtr->unk181B = sub_0806F1A0(
            (struct Unk6F1A0 *)0x08091208,
            b->unk14,
            *(s16 *)0x08091204);
    }
    if (a->unk84 >= 0)
        sub_0806D958((struct Unk6D958 *)a);
    gMainWorkPtr->unk1690 =
        (void *)(0x08091208 + gMainWorkPtr->unk181B * 0x84);
    sub_08043C70(
        a,
        gMainWorkPtr->unk1690,
        0x104,
        (u16)index,
        d);
    if (c != 0)
    {
        coords = (s32 *)sub_08062A14();
        sub_0806C78C((s32)coords, a, (s16)index);
    }
}
