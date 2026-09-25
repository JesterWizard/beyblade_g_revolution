#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08038580
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

// @ 0x08038580
s32 sub_08038580(void *a, u32 b)
{
    u32 idx = (u8)b;
    u32 idx2 = idx;
    u32 one;
    u32 off;
    u8 *dst;
    void **srcLoc;
    void *src;

    if (gUnk_030003CC != 0) {
            if (((gUnk_030003CC->unk20 >> idx) & (one = 1)) == 0) {
                srcLoc = (void **)gData_080BB8C0;
                off = idx << 5;
                dst = (u8 *)0x05000200 + off;
                src = *srcLoc;
                _08073C4C(a, dst, 0x20, src);
                gUnk_030003CC->unk20 |= one << idx;
            }
        gUnk_030003CC->unk22[idx2] += 1;
    }
}

