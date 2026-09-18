#include "global.h"

// @ 0x0804ced4
void sub_0804B4B4(struct Unk2F520 *a)
{
    s8 field2D5;
    s16 doubled;

    field2D5 = a->unk2D5;
    doubled = a->unk2FC;
    doubled = doubled * 2;
    sub_08061D68((u16)(doubled + 5), 0xF, 4, 0x1A);
    doubled = doubled + 6;
    sub_08061D68((u16)doubled, 0xF, 4, 0x1A);
    doubled = ((s32)field2D5 << 24) >> 23;
    sub_08061D68((u16)(doubled + 5), 0xE, 4, 0x1A);
    doubled = doubled + 6;
    sub_08061D68((u16)doubled, 0xE, 4, 0x1A);
}
