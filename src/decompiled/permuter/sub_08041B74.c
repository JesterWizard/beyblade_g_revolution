/* match-compiler: old_agbcc */
/* Permuter best for sub_08041B74: score 10 (seed score 1075), 2026-09-27.
 * BYTE-MATCHES retail (162/162 under old_agbcc; the 10 was the alignment nop),
 * but only via two permuter tricks: the chained unk08/unk04 store and taking the
 * slot-clearing NULL from `(void *)(s32)(count = 0)`. The second is not semantic
 * C; readable rewrites of it (NULL via a local, `count = 0;` first) do not match. */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

void sub_08041B74(void *a, void *b)
{
  s16 i;
  s16 count;
  struct Unk68574 **slot;
  i = 0;
  count = gData_03000504[0];
  if (count > 0)
  {
    for (; i < ((s16) gData_03000504[0]); i++)
    {
      slot = &gData_03000480[i];
      if ((((*slot) != ((void *) 0)) && ((*slot)->unkD4 == a)) && ((*slot)->unkD8 == b))
      {
        if ((*slot)->unkC8 != ((void *) 0))
        {
          sub_08059D08((struct Unk59D08 *) (*slot)->unkC8);
          (*slot)->unkC8 = (void *) 0;
        }
        sub_08068808(*slot);
        (*slot)->unk08 = ((*slot)->unk04 = -0x4000);
        *slot = gData_03000480[(s16) (--gData_03000504[0])];
        gData_03000480[(s16) gData_03000504[0]] = (void *) (s32) (count = 0);
        return;
      }
    }

  }
}
