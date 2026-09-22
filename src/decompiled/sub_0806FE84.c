/* match-compiler: old_agbcc */
#include "global.h"

void sub_0806FE84(void *arg)
{
    struct Unk6FE84 *state;
    struct Unk6FE84 *previous;
    struct Unk6FE84 *next;
    s32 status;
    s32 bit;

    state = arg;
    previous = state->unk00;
    next = state->unk04;
    status = state->unk24;
    if (status >= 0 && (state->unk20 & 1) == 0)
    {
        bit = 1 << (state->unk16 - 5);
        sub_0806FBF8(status, bit);
    }
    state->unk24 = -1;
    if (previous != 0)
        previous->unk04 = next;
    else
        *(struct Unk6FE84 **)(void *)&gUnk_030040A4 = next;
    if (next != 0)
        next->unk00 = previous;
    {
        struct Unk6FE84 **free_loc;

        free_loc = (struct Unk6FE84 **)(void *)&gUnk_030040AC;
        state->unk04 = *free_loc;
        *free_loc = state;
    }
    if (state->unk30 != 0)
    {
        BtlObjListMoveToHead((struct BtlObj *)state);
        state->unk30 = 0;
    }
    gUnk_030040B4++;
    sub_0806F8C4((struct Unk6F8C4 *)(*(void **)(void *)&gUnk_030040A4));
}
