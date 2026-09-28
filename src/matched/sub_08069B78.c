#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069b78
/* match-compiler: old_agbcc */
// Set the priority of BG0-BG3 (sub_08069988 returns the BGxCNT register).
void BgSetPriorities(u32 a, u32 b, u32 c, u32 d)
{
    u8 bg0 = a;
    u8 bg1 = b;
    u8 bg2 = c;
    u8 bg3 = d;

    ((struct BgCnt *)sub_08069988(0))->priority = bg0;
    ((struct BgCnt *)sub_08069988(1))->priority = bg1;
    ((struct BgCnt *)sub_08069988(2))->priority = bg2;
    ((struct BgCnt *)sub_08069988(3))->priority = bg3;
}

