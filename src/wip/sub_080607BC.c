#include "global.h"

void sub_080607BC(void)
{
    register struct Unk0758 **state_loc;
    register struct Unk0758 *state;
    register u8 mode;
    register u16 allones;

    state_loc = &gUnk_03000758;
    state = *state_loc;
    mode = state->unk06;
    if (mode != 1)
        return;
    if (state->unk07 == 0)
    {
        REG_BLDALPHA = state->unk00;
        REG_BLDY = state->unk04;
        if (state->unk08 != 0)
            state->unk08--;
        else
        {
            state->unk08 = state->unk09;
            state = *state_loc;
            state->unk04 = state->unk02 + state->unk04;
            if ((s16)state->unk04 == 0x0F)
            {
                allones = 0xFFFF;
                state->unk02 = state->unk02 | allones;
            }
            if (state->unk04 == 0)
                state->unk02 = mode;
        }
    }
    else if (state->unk07 == 1)
    {
        REG_BLDALPHA = state->unk00;
        REG_BLDY = state->unk04;
    }
}
