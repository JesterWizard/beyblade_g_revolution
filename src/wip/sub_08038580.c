/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08038580
// 59/92 same-size on old_agbcc. Register/scheduling: one is created before the
// halfword load, and the palette base is loaded before gData_080BB8C0.
void sub_08038580(void *a, u32 b)
{
    u32 idx = (u8)b;
    u32 idx2 = idx;
    struct Unk3CC *obj;
    u32 one;

    obj = gUnk_030003CC;
    if (obj != 0) {
        one = 1;
        if (((obj->unk20 >> idx) & one) == 0) {
            _08073C4C(a, (u8 *)gData_05000200 + (idx << 5), 0x20,
                (void *)*gData_080BB8C0);
            obj = gUnk_030003CC;
            obj->unk20 |= one << idx;
        }
        obj = gUnk_030003CC;
        obj->unk22[idx2] += 1;
    }
}
