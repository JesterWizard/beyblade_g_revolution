#include "global.h"

void sub_0805264C(struct Unk2F520 *data, u32 index)
{
    register struct Unk2F520 *ptr asm("r5");
    u8 *base;
    u32 offset;
    void *callback;
    u32 mode;
    u16 position;

    ptr = data;
    base = (u8 *)0x080995AC;
    offset = index << 4;
    base += 8;
    callback = *(void **)(base + offset);
    if (callback != 0)
        _08073C48(ptr, (void *)index, callback);

    mode = 0x0F;
    if (index == ptr->unk2D5)
        mode = 0x0E;
    index <<= 1;
    position = index + 5;
    sub_08061D68(position, mode, 4, 0x19);
    position = index + 0x0B;
    sub_08061D68(position, mode, 4, 0x19);
}
