#include "global.h"

// @ 0x0805da70
void sub_0805DA70(void)
{
    struct Unk0748 *p;
    void *src;
    void **cpuSet;

    p = *(struct Unk0748 **)gUnk_03000748;
    if (p != 0 && p->unk80 != 0)
    {
        src = p->unk164;
        cpuSet = (void **)0x080BB8C0;
        _08073C4C(src, (void *)0x05000340, 0x20, *cpuSet);
    }
}

