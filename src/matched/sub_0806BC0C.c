#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806bc0c
// Bind a resource header: resolve its three section offsets, then build up to
// 64 entry pointers (warns and clamps when the header asks for more).
void ResourceBind(void *arg, void *source_arg)
{
    struct Unk6BC0C *state = arg;
    struct Unk6BC0CSource *source = source_arg;
    s16 count;
    s16 i;

    state->unk00 = source;
    state->unk04 = (u8 *)source + source->unk10;
    state->unk08 = (u8 *)source + source->unk14;
    state->unk0C = (u8 *)source + source->unk18;
    count = source->unk04;
    if (count > 0x40)
    {
        count = 0x40;
        DebugMessage((void *)0x083D1D3C, source);
    }
    for (i = 0; i < count; i++)
        state->unk14[i] = sub_0806DEC8((struct UnkDEC8 *)state, i);
    state->unk114 = 0;
    state->unk10 = 0;
    state->unk118 = 0;
}

