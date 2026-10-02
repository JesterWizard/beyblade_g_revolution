#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_080473F8 */
// @ 0x080473f8

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

/* fn: sub_0804745C */
// @ 0x0804745c
void SparklesDestroy(void)
{
  struct SparklePool **slot;
  s32 i;
  struct SparkleSlot *p;
  if ((*((struct SparklePool **) 0x03000630)) != 0)
  {
    i = 0;
    slot = &(*((struct SparklePool **) 0x03000630));
    do
    {
      p = (*slot)->slots[i];
      if (p != 0)
      {
        BtlObjPoolFree(p);
        (*slot)->slots[i] = 0;
      }
      i++;
    }
    while (i <= 0xF);
  }
  if ((*((void **) 0x03000638)) != 0)
  {
    HeapFree(*((void **) 0x03000638));
    *((void **) 0x03000638) = 0;
  }
  *((struct SparklePool **) 0x03000630) = 0;
}

/* fn: sub_080474AC */
// @ 0x080474ac
// Per-frame update of the gData_03000630 sparkle pool: count unk44 down to
// re-arm unk40 with a random delay, then count unk40 down, scattering the 16
// sprites randomly each frame and parking them off-screen when it expires.
void SparklesUpdate(void)
{
    s32 i;

    if (gData_03000198->unk1825 == 0 || gData_03000630 == NULL || (gData_03000198->unk1808 & 1) == 0)
        return;
    if (gData_03000630->unk44 > 0 && gData_03000198->unk1827 != 0)
    {
        if (--gData_03000630->unk44 == 0)
            gData_03000630->unk40 = (RandRange(0x1E) + 0x1E) << 6;
        return;
    }
    if (gData_03000630->unk40 > 0 && gData_03000198->unk1827 != 0)
    {
        if (--gData_03000630->unk40 == 0)
        {
            gData_03000630->unk44 = 0xE1 << 5;
            for (i = 0; i <= 0x0F; i++)
            {
                gData_03000630->slots[i]->x = -0x4000;
                gData_03000630->slots[i]->y = -0x4000;
            }
        }
        else
        {
            for (i = 0; i <= 0x0F; i++)
            {
                gData_03000630->slots[i]->x = RandRange(0xE8) << 8;
                gData_03000630->slots[i]->y = RandRange(0x98) << 8;
                gData_03000630->slots[i]->unk18 = RandRange(4);
            }
        }
    }
}

/* fn: sub_08047594 */
// @ 0x08047594

void SparklesHide(void)
{
    s32 i;
    struct SparkleSlot *slot;

    if (gData_03000630 != 0)
    {
        for (i = 0; i < 16; i++)
        {
            slot = gData_03000630->slots[i];
            slot->x = -0x4000;
            slot->y = -0x4000;
        }
    }
}

/* fn: sub_080475C4 */
// @ 0x080475c4
/* match-flags: -fprologue-bugfix */

void SparklesSaveTimers(void)
{
    struct SparklePool *src;

    src = gUnk_03000630;
    if (src != 0)
    {
        gMainWorkPtr->unk1798 = src->unk40;
        gMainWorkPtr->unk179C = src->unk44;
    }
}

/* fn: sub_080475F4 */
// @ 0x080475f4
/* match-flags: -fprologue-bugfix */

void SparklesRestoreTimers(void)
{
    struct SparklePool *dst;

    dst = gUnk_03000630;
    if (dst != 0)
    {
        dst->unk40 = gMainWorkPtr->unk1798;
        dst->unk44 = gMainWorkPtr->unk179C;
    }
}
