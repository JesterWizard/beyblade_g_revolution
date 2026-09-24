#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08066b10
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

u8 sub_08066B10(struct Unk66BC4 *a, u32 index)
{
    struct Unk66BC4 *state;
    u8 result;
    s32 length;
    u8 idx;

    state = a;
    idx = (u8)index;
    result = 0;
    switch (idx)
    {
    case 9:
        gUnk_030009A8 = 1 ^ gUnk_030009A8;
        sub_08066BC4(state, 0x1B);
        sub_08066BF0(state);
        break;
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
    default:
        length = sub_08073078(gUnk_030009AC);
        if (length > 0x0E)
            break;
        sub_080733BC(gUnk_030009AC, idx, 0x20);
        sub_08066BC4(state, (u16)(state->unk308 * 10 + state->unk304));
        break;
    }
    return result;
}

