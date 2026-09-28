#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068e54
/* match-compiler: old_agbcc */
void sub_08068E54(struct MapLayer *a)
{
    struct MapLayer *state;
    s32 scale;
    s32 delta_x;
    s32 x;
    s32 y;

    state = a;
    x = state->deltaX;
    x += state->unk1C;
    state->deltaX = x;
    y = state->deltaY;
    y += state->unk20;
    state->deltaY = y;
    state->unk54 = x;
    state->unk58 = y;
    BgMapScroll(state, x, y);
    if ((state->unk64 & 1) != 0)
        AffineBgUpdate(state);
    scale = state->unk24;
    if (scale != 0)
    {
        y = state->deltaX;
        delta_x = (y * scale) >> 8;
        x = state->deltaY;
        scale = (x * scale) >> 8;
        y -= delta_x;
        state->deltaX = y;
        x -= scale;
        state->deltaY = x;
        if (delta_x == 0)
        {
            if (y != 0)
                state->deltaX = delta_x;
        }
        if (scale == 0)
        {
            if (state->deltaY != 0)
                state->deltaY = scale;
        }
    }
}

