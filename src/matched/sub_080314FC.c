#include "global.h"

// @ 0x080314FC
// Sets battle-work field @ +0x118 to 0x3C (battle init path).
void sub_080314FC(void)
{
    gBattleWork->unk118 = 0x3C;
}
