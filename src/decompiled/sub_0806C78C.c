#define sub_0806DF38 sub_0806DF38_proto
#include "global.h"
#undef sub_0806DF38
u16 sub_0806DF38(void *a, struct UnkDF38Entry *out, s32 matchVal, u32 maxCount, s32 fifth);

s32 sub_0806C78C(void *a, void *b, s32 c)
{
    struct UnkDF38Entry out;
    s32 shifted;
    s32 stride;

    shifted = sub_0806DF38(a, &out, 0, 1, c) << 16;
    if (shifted == 0)
        return shifted;
    if (*out.unk00 <= 1)
        return (shifted = 0);
    stride = out.unk04 << 10;
    if (out.unk04 == *out.unk00 - 1)
        stride -= 0x10;
    sub_0806C704(a, b, out.unk08, stride);
    return 1;
}
