/* match-compiler: old_agbcc */
#include "global.h"

void sub_08038580(void *a, u32 b)
{
    u32 idx = (u8)b;
    u32 idx2 = idx;
    u32 one;

    if (gUnk_030003CC != 0) {
            void *src;
            if (((gUnk_030003CC->unk20 >> idx) & (one = 1)) == 0) {
                src = (void *)*gData_080BB8C0;
                _08073C4C(a, (u8 *)gData_05000200 + (idx << 5), 0x20, src);
                gUnk_030003CC->unk20 |= one << idx;
            }
        gUnk_030003CC->unk22[idx2] += 1;
    }
}
