#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080473f8
#include "global.h"
#include "data_symbols.h"

struct SparklePool;
struct SparkleSlot;

// @ 0x080473f8
// Allocate the 0x48-byte pool, publish it through 0x03000638, take the slot
// pointer out of its first word into 0x03000630 and seed unk44, then fill the 16
// slots and hand each to sub_0806FF58.
// Two things are load-bearing: the call is `(slot, src, -0x4000, -0x4000, 0, 1,
// 0, 0)` (the seed had the last four arguments reversed), and both pool words go
// through distinct symbols (asm/data_symbols.s) -- as literals agbcc folds the
// second address into an offset off the first and picks the wrong registers.
void SparklesCreate(void)
{
    void *tmp;
    struct SparklePool *pool;
    struct SparkleSlot *slot;
    s32 i;

    tmp = HeapAlloc(0x48);
    *(u32 *)gData_03000638 = (u32)tmp;
    gData_03000630 = *(struct SparklePool **)tmp;
    pool = gData_03000630;
    pool->unk44 = 0x1C20;

    for (i = 0; i <= 0xF; i++)
    {
        slot = BtlObjPoolAlloc(2);
        gData_03000630->slots[i] = slot;
        SpriteInitFromTemplate((struct Sprite *)slot, (void *)0x081193C0, 0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    }
}

