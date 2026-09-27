#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080385dc
/* match-compiler: old_agbcc */
/* Release palette slots lo..hi: clear their in-use bits and reset key/refcount to 0xFFFF. */
void sub_080385DC(u16 lo, u16 hi)
{
    s32 i;
    struct Unk3CC *slots;

    for (i = lo; i <= hi; i++)
    {
        slots = gUnk_030003CC;
        slots->unk20 &= ~(1 << i);
        slots->unk00[i] |= 0xFFFF;
        slots->unk22[i] |= 0xFFFF;
    }
}

