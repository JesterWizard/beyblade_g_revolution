#include "global.h"

// @ 0x0806d748
u8 sub_0806D748(struct Unk6D748 *a, void *b, u32 c, u16 d)
{
    u8 result;
    void *handler;

    result = 1;
    if (a->unk94 != 0)
    {
        handler = a->unk94->unk08;
        if (handler != 0)
            result = (u8)_08073C50(a, b, (void *)c, (void *)(u32)d);
    }
    return result;
}
