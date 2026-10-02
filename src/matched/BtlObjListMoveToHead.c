#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806ff28
/* match-flags: -fprologue-bugfix */
void BtlObjListMoveToHead(struct BtlObj *a)
{
  struct BtlObj *r3;
  u32 r0;
  struct BtlObjNode *r2;
  struct BtlObjNode *r1;
  u32 loc;
  struct BtlObjNode **new_var;
  r3 = a;
  r0 = r3->unk19;
  if (r0 == 0)
  {
    r2 = r3->next;
    r1 = r3->prev;
    if (r2 != 0)
    {
      r2->prev = r1;
    }
    else
    {
      r0 = (u32) ((struct BtlObjNode **) 0x030040B8);
      *((struct BtlObjNode **) r0) = r1;
    }
    if (r1 != 0)
    {
      r1->next = r2;
    }
    new_var = (struct BtlObjNode **) 0x030040A8;
    loc = (u32) new_var;
    ;
    r3->prev = (struct BtlObjNode *) (*((u32 *) loc));
    *((struct BtlObj **) loc) = r3;
  }
}
