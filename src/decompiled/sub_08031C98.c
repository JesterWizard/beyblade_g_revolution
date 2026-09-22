#include "global.h"

void sub_08031C98(struct Unk346C0 *a)
{
    u8 *index_ptr;
    u8 index;
    struct Unk002A0 *state;
    s32 stride;

    index_ptr = &a->unk30C;
    index = *index_ptr;
    if (gBattleWork->unk208C[index] >= 0)
    {
        gBattleWork->unk208C[index]--;
    }
    else
    {
        state = &gUnk_030002A0;
        stride = 0x2C;
        state->records[index].unk0C--;
        if (state->records[*index_ptr].unk0C <= 0x32)
        {
            gBattleWork->unk208C[index] = 0x1E;
            if (state->records[*index_ptr].unk0C <= 0x14)
                gBattleWork->unk208C[*index_ptr] = 0x0A;
        }
        else
        {
            gBattleWork->unk208C[index] =
                *(s32 *)((u8 *)&state->records[0].unk18 + *index_ptr) * 10;
        }
        if (stride == 0)
            state = 0;
    }

    sub_080320CC();
    sub_08031204();
}
