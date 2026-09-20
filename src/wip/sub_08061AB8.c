#include "global.h"

void sub_08061AB8(void)
{
    register u32 *count_loc asm("r6");
    register struct Unk0798 **work_loc asm("r5");
    register struct Unk0770 *table asm("r7");
    register void *buffer asm("r4");

    count_loc = (u32 *)0x03000794;
    if (*count_loc == 4)
        return;
    work_loc = (struct Unk0798 **)0x03000798;
    buffer = sub_0806A3A4((*work_loc)->unk94 << 5);
    table = (struct Unk0770 *)0x03000770;
    table[*count_loc].unk00 = buffer;
    if (buffer == 0)
        return;
    _08073C4C(
        (void *)(VRAM + ((u32)(*work_loc)->unk5D << 14)),
        *(void **)buffer,
        (*work_loc)->unk94 << 5,
        *(void **)0x080BB8C0);
    table[*count_loc].unk04 = (*work_loc)->unk90;
    table[*count_loc].unk06 = (*work_loc)->unk92;
    *count_loc += 1;
}
