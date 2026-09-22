#include "global.h"

void BtlObjFree(void *arg)
{
    struct Unk6A434 *state;
    struct Unk6A4D8Node *previous;
    struct Unk6A4D8Node *next;
    u32 key;

    state = arg;
    previous = state->unk0C;
    next = state->unk08;
    key = state->unk00;
    if (key == 0)
        DebugPrint((void *)0x083D1B38);
    if (next == 0)
    {
        if (previous == 0)
        {
            if (key <= 0x0203FFFF)
                gUnk_03000B30 = previous;
            else
                gUnk_03003F44 = previous;
            goto finish;
        }
        if (key <= 0x0203FFFF)
            gUnk_03000B30 = previous;
        else
            gUnk_03003F44 = previous;
        previous->unk08 = 0;
    }
    else
    {
        next->unk0C = previous;
        if (previous != 0)
            previous->unk08 = next;
    }
finish:
    if (key <= 0x0203FFFF)
        gUnk_03000B3C--;
    else
        gUnk_03003F48--;
    state->unk04 = 0;
    state->unk00 = 0;
    state->unk0C = 0;
    state->unk08 = 0;
}
