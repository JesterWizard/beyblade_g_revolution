#include "global.h"
#include "data_symbols.h"

extern void sub_08067BB8(void *a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);

// @ 0x080419b0
void *sub_080419B0(u32 a, u32 b, u32 c, u32 d)
{
    void *base;
    s16 count;
    void *slot;
    s16 newCount;

    base = (void *)gData_03000534[0];
    if (base == 0)
        return 0;
    count = *(s16 *)gUnk_03000504;
    if (count > 0x1F)
        return 0;
    slot = (u8 *)base + count * 0xDC;
    sub_08067BB8(slot, (void *)b, (s32)a, (s32)c, (s32)d, 0, -1);
    *(s16 *)((u8 *)slot + 0xBC) = (s16)~d;
    ((void **)gUnk_03000480)[count] = slot;
    ((void **)gUnk_03000480)[count + 1] = 0;
    newCount = count + 1;
    *(s16 *)gUnk_03000504 = newCount;
    return (u8 *)base + count * 0xDC;
}
