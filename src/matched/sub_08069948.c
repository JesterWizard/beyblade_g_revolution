#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08069948
/* match-compiler: old_agbcc */
u16 *BgGetVofsReg(u8 sel)
{
    switch (sel)
    {
    case 0: return (u16 *)0x04000012;
    case 1: return (u16 *)0x04000016;
    case 2: return (u16 *)0x0400001A;
    case 3: return (u16 *)0x0400001E;
    }
}

