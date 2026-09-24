#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068e54
/* match-compiler: old_agbcc */
void sub_08068E54(struct Unk68E54 *a)
{
    struct Unk68E54 *state;
    s32 scale;
    s32 delta_x;
    s32 x;
    s32 y;

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
        y = state->unk14;
        delta_x = (y * scale) >> 8;
        x = state->unk18;
        scale = (x * scale) >> 8;
        y -= delta_x;
        state->unk14 = y;
        x -= scale;
        state->unk18 = x;
        if (delta_x == 0)
        {
            if (y != 0)
                state->unk14 = delta_x;
        }
        if (scale == 0)
        {
            if (state->unk18 != 0)
                state->unk18 = scale;
        }
    }
}

