#include "global.h"

// @ 0x08048168
void sub_08048168(struct Unk2F520 *a)
{
    s8 *fieldPtr;

    sub_08061D68(5, 0xF, 0xB, 0x12);
    sub_08061D68(6, 0xF, 0xB, 0x12);
    sub_08061D68(7, 0xF, 0xB, 0x12);
    sub_08061D68(8, 0xF, 0xB, 0x12);
    fieldPtr = &a->unk2D5;
    sub_08061D68((u16)((((s32)*fieldPtr << 17) + 0x50000) >> 16), 0xE, 0xB, 0x12);
    sub_08061D68((u16)((((s32)*fieldPtr << 17) + 0x60000) >> 16), 0xE, 0xB, 0x12);
}
