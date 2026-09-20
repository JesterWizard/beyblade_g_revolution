#include "global.h"

u8 sub_0806D748(struct Unk6D748 *arg0, void *arg1, u32 arg2, u32 arg3)
{
    void *handler;
    struct Unk6D748 *p;
    void *b;
    u8 result;

    p = arg0;
    b = arg1;
    result = 1;

    if (p->unk94 != 0)
    {
        handler = p->unk94->unk08;
        if (handler != 0)
            result = (u8)_08073C50(p, b, (void *)arg2, (void *)arg3);
    }

    return result;
}
