#include "global.h"

// @ 0x080442fc
void sub_080442FC(
    struct Unk442FC *a,
    struct Unk442FCInput *b,
    u32 c,
    u32 d)
{
    u32 flag;
    u32 arg4;
    u32 index;
    u32 mw;
    u32 slot;
    u32 p181b;
    u32 arg2;
    u32 r0;
    u32 r1;
    u32 r3;

    index = 0;
    flag = c;
    arg4 = d;
    if (b != 0)
    {
        index = b->unk16;
        gMainWorkPtr->unk181B = (u8)sub_0806F1A0(
            (struct Unk6F1A0 *)gData_08091208,
            b->unk14,
            gData_08091204[0]);
    }
    if (a->unk84 >= 0)
        sub_0806D958((struct Unk6D958 *)a);
    mw = *(u32 *)gMainWorkPtrLoc;
    slot = mw + 0x1690;
    p181b = mw + 0x181B;
    r3 = *(u8 *)p181b;
    r1 = r3 << 5;
    r1 += r3;
    r1 <<= 2;
    r0 = (u32)gData_08091208;
    r1 += r0;
    *(u32 *)slot = r1;
    arg2 = 0x82;
    arg2 <<= 5;
    index <<= 16;
    r3 = index >> 16;
    sub_08043C70(a, (void *)r1, arg2, r3, arg4);
    if (flag != 0)
        sub_0806C78C((s32)sub_08062A14(), a, (s32)index >> 16);
}
