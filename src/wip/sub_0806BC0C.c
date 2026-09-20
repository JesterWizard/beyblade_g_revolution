#include "global.h"

void sub_0806BC0C(void *arg, void *source_arg)
{
    register struct Unk6BC0C *state;
    register s32 limit;
    register s32 current;
    struct Unk6BC0CSource *source;
    u16 index;

    state = arg;
    source = source_arg;
    state->unk00 = source;
    state->unk04 = (u8 *)source + source->unk10;
    state->unk08 = (u8 *)source + source->unk14;
    state->unk0C = (u8 *)source + source->unk18;
    current = source->unk04;
    if ((s16)source->unk04 > 0x40)
    {
        current = 0x40;
        sub_08067A9C((void *)0x083D1D3C, source);
    }
    limit = current << 16;
    index = 0;
    current = 0;
    while (current < limit)
    {
        current = (s16)index;
        state->unk14[current] = sub_0806DEC8(
            (struct UnkDEC8 *)state,
            current);
        current++;
        current <<= 16;
        index = (u16)(current >> 16);
    }
    state->unk114 = 0;
    state->unk10 = 0;
    state->unk118 = 0;
}
