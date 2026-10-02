#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_0802E1EC */
// @ 0x0802e1ec
s8 ExpLevel(void)
{
    return ExpBracket(gMainWorkPtr->expPoints);
}

/* fn: sub_08042B78 */
// @ 0x08042b78
s32 ExpBracketTop(s32 level)
{
  s32 key;
  s32 minusOne;
  s32 sentinel;
  const u32 *base;
  const u32 *entry;
  s32 first;
  key = level;
  base = (const u32 *) 0x080908BC;
  first = (s32) base[0];
  minusOne = -1;
  if (first != minusOne)
  {
    sentinel = minusOne;
    entry = base;
    for (;;)
    {
      if (base[0] == ((u32) key))
        return entry[3];
      entry += 2;
      base += 2;
      if (entry[0] == ((u32) sentinel))
        break;
    }

  }
  return -1;
}

/* fn: sub_08042BB0 */
// @ 0x08042bb0
s32 ExpBracketBase(s32 level)
{
  s32 key;
  s32 minusOne;
  s32 sentinel;
  const u32 *base;
  const u32 *entry;
  const u32 *valueEntry;
  u32 first;
  key = level;
  base = (const u32 *) 0x080908BC;
  first = base[0];
  minusOne = -1;
  if (first != ((u32) minusOne))
  {
    sentinel = minusOne;
    entry = base;
    valueEntry = base;
    for (;;)
    {
      if ((*entry) == ((u32) key))
        return valueEntry[1];
      valueEntry += 2;
      entry += 2;
      if ((*valueEntry) == ((u32) sentinel))
        break;
    }

  }
  return -1;
}

/* fn: sub_08042BE8 */
// @ 0x08042be8
s32 ExpBracket(s32 points)
{
    s32 i;

    for (i = 0; gData_080908BC[i].level != -1; i++)
    {
        if (points >= gData_080908BC[i].minPoints && points < gData_080908BC[i + 1].minPoints)
            return gData_080908BC[i].level;
    }
    return -1;
}

/* fn: sub_08042F4C */
// @ 0x08042f4c

void MatchBladerExperience(s32 expBase, s32 strengthBase, s32 bladeId, s32 gained)
{
    struct Unk42E78 *row;
    s32 old;
    s32 scaled;

    row = (struct Unk42E78 *)BeybladeCollectionEntry((u32)bladeId);
    if (row != 0)
    {
        old = row->bitBeastExp;
        scaled = 0x64 * gained;
        row->bitBeastExp = expBase + scaled;
        scaled = strengthBase + gained;
        if (scaled > 0)
            strengthBase = scaled;
        row->strength = (u8)strengthBase;
        DebugPrint((void *)gData_083A2CF4, (void *)gData_083A2D28, bladeId, old, row->bitBeastExp, gained);
    }
}
