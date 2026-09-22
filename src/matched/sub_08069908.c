#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069908
/* match-compiler: old_agbcc */
u16 *BgGetHofsReg(u8 sel)
{
    switch (sel)
    {
    case 0: return (u16 *)0x04000010;
    case 1: return (u16 *)0x04000014;
    case 2: return (u16 *)0x04000018;
    case 3: return (u16 *)0x0400001C;
    }
}

