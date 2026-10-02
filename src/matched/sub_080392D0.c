#include "global.h"

// @ 0x080392d0
void sub_080392D0(void)
{
    if ((gBattleWork->boostMeterText.unk10 >> 8) > -0xF0)
        Unk62044OffsetPoints(&gBattleWork->boostMeterText, -8, 0);
    else
        GlyphTextFree(&gBattleWork->boostMeterText);

    if ((gBattleWork->powerMeterText.unk10 >> 8) <= 0xEF)
        Unk62044OffsetPoints(&gBattleWork->powerMeterText, 8, 0);
    else
        GlyphTextFree(&gBattleWork->powerMeterText);
}

