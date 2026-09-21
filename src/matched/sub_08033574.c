#include "global.h"

// @ 0x08033574
/* match-compiler: old_agbcc */
void sub_08033574(void)
{
    struct BattleWork *w;
    u8 shifted;
    u8 *fieldPtr;

    w = gBattleWork;
    if (w->unk2088 == 1)
    {
        fieldPtr = &w->unk1FE6;
        shifted = *fieldPtr >> 1;
        sub_08068808((struct Unk68574 *)(fieldPtr - 0x3A));
        sub_08038638(shifted);
    }
    gBattleWork->unk2089 = 0xFF;
    gBattleWork->unk2088 = 0;
}

