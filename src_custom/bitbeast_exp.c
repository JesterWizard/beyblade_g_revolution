#include "global.h"
#include "ram_map.h"

/*
 * Retail sub_0803EAC0. The signed byte selects direction: negative subtracts
 * 16, otherwise adds 16, then the halfword is masked with 0x3FFF. The next
 * +16 past 16383 wraps to 0. The blade index is the word at 0x03000468.
 */
APPEND_TEXT void BitBeastAdjustExp__Replacement(s32 delta)
{
    struct Unk42E78 *row;
    s32 exp;

    row = (struct Unk42E78 *)sub_08042E78(*(u32 *)gUnk_03000468);
    exp = (u16)row->bitBeastExp;
    if ((s8)delta < 0)
        exp -= 16;
    else
        exp += 16;
    if (gRuntimeConfig.uncapBitBeastExp == FALSE)
        exp &= 0x3FFF;
    else if (exp < 0)
        exp = 0;
    else if (exp > 32767)
        exp = 32767;
    row->bitBeastExp = (s16)exp;
}
