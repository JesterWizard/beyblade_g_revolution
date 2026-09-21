/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

// @ 0x0804495c
// 34/60 same-size (56.7%). do-while form matches retail's `subs r2,#1; cmp; bge`
// loop; remaining diff is in the src-pointer setup (table at 0x08094E00 indexed by
// the s8 unk181F) and register choice for dst/n.
void sub_0804495C(void)
{
    u16 *src = *(u16 **)((u8 *)0x08094E00 + gMainWorkPtr->unk181F * 4);
    u16 *dst = (u16 *)0x050001C0;
    s32 n = 0x1F;

    do
    {
        *dst++ = *src++;
    } while (--n >= 0);
}
