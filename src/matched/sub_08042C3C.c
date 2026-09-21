#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042c3c
s32 sub_08042C3C(s32 a)
{
  s32 key;
  s32 minusOne;
  s32 sentinel;
  const u32 *entry;
  const u32 *valueEntry;
  u32 first;
  key = a;
  entry = (const u32 *) 0x0809094C;
  first = entry[0];
  minusOne = -1;
  if (first != ((u32) minusOne))
  {
    sentinel = minusOne;
    valueEntry = entry;
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
