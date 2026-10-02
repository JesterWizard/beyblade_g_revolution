#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806a434
#include "global.h"
#include "ram_map.h"
void HeapFree(void *arg)
{
    struct Unk6A434 *state;
    struct Unk6A4D8Node *previous;
    struct Unk6A4D8Node *next;

    state = arg;
    previous = state->unk0C;
    next = state->unk08;
    if (state->unk00 == 0)
        DebugPrint((void *)0x083D1B38);
    if (next == 0)
    {
        if (previous == 0)
        {
            if (state->unk00 <= 0x0203FFFF)
                gUnk_03000B30 = previous;
            else
                gUnk_03003F44 = previous;
        }
        else
        {
            if (state->unk00 <= 0x0203FFFF)
                gUnk_03000B30 = previous;
            else
                gUnk_03003F44 = previous;
            if (previous != 0)
                previous->unk08 = 0;
        }
    }
    else
    {
        next->unk0C = previous;
        if (previous != 0)
            previous->unk08 = next;
    }
    if (state->unk00 <= 0x0203FFFF)
        gUnk_03000B3C--;
    else
        gUnk_03003F48--;
    state->unk04 = 0;
    state->unk00 = 0;
    state->unk0C = 0;
    state->unk08 = 0;
}

