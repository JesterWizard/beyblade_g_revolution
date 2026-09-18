#include "global.h"

// @ 0x0804a4e0
void sub_0804A4E0(struct Unk2F520 *a)
{
    s8 field2D5;
    u8 field2FC;
    s16 doubled;

    field2D5 = a->unk2D5;
    field2FC = a->unk2FC;
    sub_08061BE8();
    doubled = ((s32)field2FC << 24) >> 23;
    sub_08061D68((u16)(doubled + 5), 0xF, 4, 0x1A);
    doubled = doubled + 6;
    sub_08061D68((u16)doubled, 0xF, 4, 0x1A);
    doubled = ((s32)field2D5 << 24) >> 23;
    sub_08061D68((u16)(doubled + 5), 0xE, 4, 0x1A);
    doubled = doubled + 6;
    sub_08061D68((u16)doubled, 0xE, 4, 0x1A);
}
