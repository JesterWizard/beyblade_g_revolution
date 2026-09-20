#include "global.h"

s32 sub_0806C78C(void *arg0, void *arg1, s32 arg2)
{
    s32 saved;
    struct UnkDF38Entry out[1];
    u16 found;
    s32 stride;

    saved = arg2;
    found = sub_0806DF38(arg0, out, 0, 1);
    if (!found)
        return 0;

    if (*out[0].unk00 <= 1)
        return 0;

    stride = out[0].unk04 << 0xA;
    if (out[0].unk04 == *out[0].unk00 - 1)
        stride -= 0x10;

    sub_0806C704(arg0, arg1, out[0].unk08, stride);
    (void)saved;
    return 1;
}
