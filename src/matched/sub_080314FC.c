#include "global.h"

// @ 0x080314fc
#include "global.h"
#include "battle.h"
#include "ram_map.h"

// @ 0x080314FC
// Sets battle-work field @ +0x118 to 0x3C (battle init path).
void sub_080314FC(void)
{
    u8 *base;

    base = *(u8 **)gBattleWork;
    *(u32 *)(base + 0x118) = 0x3C;
}

