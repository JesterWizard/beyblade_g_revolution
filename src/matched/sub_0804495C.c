#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804495c
/* match-compiler: old_agbcc */
void sub_0804495C(void)
{
    u32 *table = gData_08094E00;
    s8 idx = gMainWorkPtr->unk181F;
    u16 *src = (u16 *)table[idx];
    u16 *dst = gData_050001C0;
    s32 n = 0x1F;

    do {
        *dst++ = *src++;
    } while (--n >= 0);
}
