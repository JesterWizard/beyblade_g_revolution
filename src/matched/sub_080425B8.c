#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080425b8
void sub_080425B8(void)
{
  u8 *addr;
  u8 mask;
  u8 value;
 // The do/while(0) block is load-bearing: splitting `addr` and `mask` into
 // separate statements changes the register assignment (retail wants the
 // 0x03000198 load before the 0x03000538 load).
 do { addr = &gMainWorkPtr->unk0479; mask = 1; } while (0);
  value = *addr;
  mask |= value;
  *addr = mask;
  gUnk_03000538->unk02 = 0x20;
  if (gMainWorkPtr->unk0462 != 8)
  {
    BtlEntitySelectByKeyDefault((struct Unk680CC *) (&gMainWorkPtr->unk0448), 8);
  }
  gMainWorkPtr->unk044C = gUnk_03000538->unk44[(s32) ((s8) gUnk_03000538->unk00)];
  gMainWorkPtr->unk0450 = gUnk_03000538->unkC4[(s32) ((s8) gUnk_03000538->unk00)];
}
