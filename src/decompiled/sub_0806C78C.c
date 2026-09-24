#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806c78c
#include "global.h"

s32 sub_0806C78C(void *a, void *b, s32 c)
{
    struct UnkDF38Entry out;
    s32 shifted;
    s32 stride;

    shifted = sub_0806DF38(a, &out, 0, 1, c) << 16;
    if (shifted == 0)
        goto done;
    if (*out.unk00 > 1)
        goto success;
    shifted = 0;
    goto done;
success:
    stride = out.unk04 << 10;
    if (out.unk04 == *out.unk00 - 1)
        stride -= 0x10;
    sub_0806C704(a, b, out.unk08, stride);
    shifted = 1;
done:
    return shifted;
}

