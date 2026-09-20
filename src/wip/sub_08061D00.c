#include "global.h"

void sub_08061D00(u16 arg0, u32 arg1)
{
    register struct Unk0798 **work_loc asm("r4");
    register u32 encoded asm("r5");
    register u16 index asm("r2");

    work_loc = (struct Unk0798 **)0x03000798;
    index = arg0;
    encoded = (arg1 << 12) | (arg1 << 28) | 0x400;
    _08073C4C(
        sub_0806BB38((*work_loc)->unk88, index),
        (void *)(VRAM + ((u32)(*work_loc)->unk5D << 14)),
        0x20,
        *(void **)0x080BB8C0);
    _08073C4C(
        (void *)encoded,
        (void *)(VRAM + ((u32)(*work_loc)->unk5C << 11)),
        0x800,
        *(void **)0x080BB8BC);
}
