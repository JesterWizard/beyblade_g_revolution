/* match-compiler: old_agbcc */
#include "global.h"

void sub_08068118(struct Unk68118 *a)
{
    struct Unk68118 *state;
    struct Unk68118Table *table;
    u16 next;
    s16 callback_arg;
    void *callback;

    state = a;
    table = (struct Unk68118Table *)(
        (u8 *)state->unk00 + state->unk00->unk18 + state->unk1C);
    next = 0;
    if ((s16)state->unk1E < (s16)(table->unk04 - 1))
    {
        next = state->unk1E + 1;
    }
    else
    {
        if ((s16)state->unk2E != -1)
        {
            callback_arg = state->unk1A;
            sub_08068020((struct Unk680CC *)state, state->unk2E, 0xFFFF);
            callback = state->unkC0;
            if (callback != 0)
                _08073C48(state, (void *)(s32)callback_arg, callback);
            return;
        }
    }
    state->unk1E = next;
    sub_08068180(
        (struct Unk680CC *)state,
        table->entries[next]);
}
