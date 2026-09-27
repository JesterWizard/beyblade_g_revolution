#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080607bc
// Blend fade tick: writes BLDCNT/BLDY from the fade state and, every
// (unk09 + 1) frames, steps the BLDY level by unk02 (bouncing at 15, and
// resetting the step when the level returns to 0).
void sub_080607BC(void)
{
    struct Unk0758 *state = gUnk_03000758;
    u32 mode = state->unk06;
    struct Unk0758 *fade;

    if (mode != 1)
        return;
    switch (state->unk07)
    {
    case 0:
        REG_BLDCNT = state->unk00;
        REG_BLDY = state->unk04;
        if (state->unk08 != 0)
        {
            state->unk08--;
            break;
        }
        state->unk08 = state->unk09;
        fade = gUnk_03000758;
        fade->unk04 += fade->unk02;
        if (fade->unk04 == 0x0F)
            fade->unk02 |= 0xFFFF;
        if (gUnk_03000758->unk04 == 0)
            gUnk_03000758->unk02 = mode;
        break;
    case 1:
        REG_BLDCNT = state->unk00;
        REG_BLDY = state->unk04;
        break;
    }
}

