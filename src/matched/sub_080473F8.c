#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080473f8
#include "global.h"
#include "data_symbols.h"

struct Unk473F8;
struct Unk474ACSlot;

// @ 0x080473f8
// Allocate the 0x48-byte pool, publish it through 0x03000638, take the slot
// pointer out of its first word into 0x03000630 and seed unk44, then fill the 16
// slots and hand each to sub_0806FF58.
// Two things are load-bearing: the call is `(slot, src, -0x4000, -0x4000, 0, 1,
// 0, 0)` (the seed had the last four arguments reversed), and both pool words go
// through distinct symbols (asm/data_symbols.s) -- as literals agbcc folds the
// second address into an offset off the first and picks the wrong registers.
void sub_080473F8(void)
{
    void *tmp;
    struct Unk473F8 *pool;
    struct Unk474ACSlot *slot;
    s32 i;

    tmp = BtlObjAlloc(0x48);
    *(u32 *)gData_03000638 = (u32)tmp;
    *(struct Unk473F8 **)gData_03000630 = *(struct Unk473F8 **)tmp;
    pool = *(struct Unk473F8 **)gData_03000630;
    pool->unk44 = 0x1C20;

    for (i = 0; i <= 0xF; i++)
    {
        slot = sub_0806FDD0(2);
        (*(struct Unk473F8 **)gData_03000630)->unk00[i] = slot;
        sub_0806FF58(slot, (void *)0x081193C0, 0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    }
}

