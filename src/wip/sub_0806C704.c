#include "global.h"

void sub_0806C704(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
    register void *source;
    register struct Unk6C704 *state;
    register void *input;
    s32 extra;
    s32 output[6];
    u32 result;

    source = arg0;
    state = arg1;
    input = (void *)arg2;
    extra = arg3;
    if ((state->unk8D & 4) != 0)
        result = sub_0806E060(source, input, output);
    else
        result = sub_0806E31C(source, input, output, extra);
    if (result != 0)
    {
        state->unk04 = (output[0] << 5) - (state->unk9A << 8);
        state->unk08 = (output[1] << 5) - (state->unk9C << 8);
        state->unk0C = (output[2] << 5) - (state->unk9E << 8);
        state->unk80 = source;
        state->unk84 = input;
        state->unk88 = extra << 8;
        state->unk44 = 0;
    }
}
