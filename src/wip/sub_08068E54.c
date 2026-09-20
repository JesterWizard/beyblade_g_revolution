#include "global.h"

void sub_08068E54(struct Unk68E54 *a)
{
    register struct Unk68E54 *state;
    register s32 scale;
    register s32 delta_x;
    register s32 x;
    register s32 y;

    state = a;
    x = state->unk14;
    x += state->unk1C;
    state->unk14 = x;
    y = state->unk18;
    y += state->unk20;
    state->unk18 = y;
    state->unk54 = x;
    state->unk58 = y;
    sub_0806960C(state);
    if ((state->unk64 & 1) != 0)
        sub_08068EC0(state);
    scale = state->unk24;
    if (scale != 0)
    {
        scale = state->unk24;
        x = state->unk14;
        delta_x = (x * scale) >> 8;
        y = state->unk18;
        scale = (y * scale) >> 8;
        x -= delta_x;
        state->unk14 = x;
        y -= scale;
        state->unk18 = y;
        if (delta_x == 0 && x != 0)
            state->unk14 = 0;
        if (scale == 0 && y != 0)
            state->unk18 = 0;
    }
}
