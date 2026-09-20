#include "global.h"

struct Unk33574State
{
    u8 filler_00[0x3A];
    u8 unk3A;
};

// @ 0x08033574
void sub_08033574(void)
{
    struct BattleWork *w;
    struct Unk33574State *state;

    w = gBattleWork;
    state = (struct Unk33574State *)&w->unk1FAC;
    if (w->unk2088 == 1)
    {
        sub_08068808((struct Unk68574 *)state);
        sub_08038638(state->unk3A >> 1);
    }
    w->unk2089 = 0xFF;
    w->unk2088 = 0;
}
