#include "global.h"

u8 sub_08066B10(struct Unk66BC4 *a, u8 index)
{
    register struct Unk66BC4 *state;
    u8 result;
    s32 length;

    state = a;
    result = 0;
    switch (index)
    {
    case 8:
        sub_0807339C(gUnk_030009AC);
        sub_08066BC4(state, 0x1C);
        break;
    case 7:
        sub_08066BC4(state, 0x1D);
        length = sub_08073078(gUnk_030009AC);
        if (length > 0)
            result = 1;
        break;
    case 9:
        gUnk_030009A8 = 1 ^ gUnk_030009A8;
        sub_08066BC4(state, 0x1B);
        sub_08066BF0(state);
        break;
    default:
        length = sub_08073078(gUnk_030009AC);
        if (length > 0x0E)
            break;
        sub_080733BC(gUnk_030009AC, index, 0x20);
        sub_08066BC4(
            state,
            (u16)(state->unk304 + state->unk308 * 10));
        break;
    }
    return result;
}
