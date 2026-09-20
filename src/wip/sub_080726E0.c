#include "global.h"

// @ 0x080726e0
void sub_080726E0(struct Unk726E0 *a, void *dst, s32 idx)
{
    void *src;
    void **cpuSet;
    register u16 off;

    if (idx < a->unk08)
    {
        cpuSet = (void **)0x080BB8C0;
        src = (u8 *)a->unk0C + idx * a->unk06 * 2;
        off = a->unk04;
        _08073C4C(src, (u8 *)dst + off * 2, a->unk06 * 2, *cpuSet);
    }
}

