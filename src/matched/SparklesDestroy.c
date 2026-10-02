#include "global.h"
#include "ram_map.h"
#include "battle.h"

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
