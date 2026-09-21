#include "global.h"

// @ 0x080726e0
void sub_080726E0(struct Unk726E0 *a, void *dst, s32 idx)
{
    void *src;
    void **cpuSet;
    u16 width;

    if (idx < a->unk08)
    {
        cpuSet = (void **)0x080BB8C0;
        width = a->unk06;
        src = (void *)((u32)a->unk0C + idx * width * 2);
        a = (struct Unk726E0 *)(u32)a->unk04;
        _08073C4C(src, (void *)((u32)dst + (u32)a * 2), width * 2, *cpuSet);
    }
}

