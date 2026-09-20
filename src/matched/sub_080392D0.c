#include "global.h"

// @ 0x080392d0
void sub_080392D0(void)
{
    if ((gBattleWork->unk1F38.unk10 >> 8) > -0xF0)
        sub_080620D4(&gBattleWork->unk1F38, -8, 0);
    else
        sub_08062044(&gBattleWork->unk1F38);

    if ((gBattleWork->unk1F10.unk10 >> 8) <= 0xEF)
        sub_080620D4(&gBattleWork->unk1F10, 8, 0);
    else
        sub_08062044(&gBattleWork->unk1F10);
}

