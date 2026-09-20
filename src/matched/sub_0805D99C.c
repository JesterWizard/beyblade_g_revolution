#include "global.h"

// @ 0x0805d99c

void sub_0805D99C(void *a)
{
    struct Unk0748 *p;

    p = *(struct Unk0748 **)gUnk_03000748;
    if (p != 0)
    {
        p->unk0C = a;
        sub_08066390(0x1B);
        sub_0804109C((void *)((u8 *)gMainWorkPtr + 0x530), sub_0806639C());
        gMainWorkPtr->unk181C = 3;
        gMainWorkPtr->unk1708 = 0;
    }
}

