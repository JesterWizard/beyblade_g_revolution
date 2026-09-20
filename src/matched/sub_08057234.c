#include "global.h"

// @ 0x08057234
#include "global.h"

void sub_08057234(struct Unk6BE08 *arg0, u32 arg1)
{
    void *entry;
    s32 ret;
    void *next;

    ret = sub_0806BE08(arg0, arg1);
    if (ret == -1)
        return;

    entry = sub_0806BDA8((struct Unk6BDA8 *)arg0, ret);
    if (entry == 0)
        return;

    ret = 0;
    while ((next = sub_0806BE20(arg0, entry, ret)) != 0)
    {
        ret++;
        sub_08056D68(next);
    }
}

