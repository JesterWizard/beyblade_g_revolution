#include "global.h"

void sub_0806184C(u16 x, u16 y)
{
    struct Unk0798 *work;
    u16 width;
    u32 bank;
    void *destination;

    work = gUnk_03000798;
    if (y >= (work->unk9A >> 3) - 1)
        return;
    width = work->unk98 >> 3;
    if (x >= width - 1)
        return;
    bank = work->unk5D;
    destination = (void *)(
        VRAM
        + (bank << 14)
        + (((u32)width << 5) * y)
        + (x << 5));
    _08073C4C(
        (void *)0,
        destination,
        0x20,
        *(void **)0x080BB8BC);
}
