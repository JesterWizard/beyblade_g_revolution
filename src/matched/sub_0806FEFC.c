#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806fefc
/* match-flags: -fprologue-bugfix */
// NOTE: `r0` is read before assignment below — retail also branches on whatever
// is left in r0 at entry (this is a void function that used to take a selector).
// Both arms of the branch are byte-identical, so the read is inert; do not
// "fix" it, the uninitialised read is what reproduces retail's codegen.
struct BtlObjNode *sub_0806FEFC(void)
{
  u32 r2;
  struct BtlObjNode *r1;
  struct BtlObjNode *r0;
  r2 = (u32) ((struct BtlObjNode **) 0x030040A8);
  r1 = *((struct BtlObjNode **) r2);
  if (r1 != 0)
  {
    if (r0)
    {
      r0 = r1->prev;
      *((struct BtlObjNode **) r2) = r0;
      r2 = (u32) ((struct BtlObjNode **) 0x030040B8);
      r0 = *((struct BtlObjNode **) r2);
    }
    else
    {
      r0 = r1->prev;
      *((struct BtlObjNode **) r2) = r0;
      r2 = (u32) ((struct BtlObjNode **) 0x030040B8);
      r0 = *((struct BtlObjNode **) r2);
    }
    if (r0 != 0)
    {
      r0->next = r1;
    }
    r0 = *((struct BtlObjNode **) r2);
    r1->prev = r0;
    r0 = 0;
    r1->next = r0;
    *((struct BtlObjNode **) r2) = r1;
  }
  r0 = r1;
  return r0;
}
