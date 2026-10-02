#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803559c
// Re-keys one of the three animation blocks (type 0..2) when its current key
// differs from `value`.
void sub_0803559C(void *obj, u32 b, u32 value)
{
    struct Unk35258 *base = obj;
    u8 type = b;

    switch (type)
    {
    case 0:
        if (base->unk1C.unk1A == value)
            break;
        AnimObjSelectSeq((struct AnimObjSeqSelect *)&base->unk1C, value, value);
        break;
    case 1:
        if (base->unkF8.unk1A == value)
            break;
        AnimObjSelectSeq((struct AnimObjSeqSelect *)&base->unkF8, value, value);
        break;
    case 2:
        if (base->unk1D4.unk1A == value)
            break;
        AnimObjSelectSeq((struct AnimObjSeqSelect *)&base->unk1D4, value, value);
        break;
    }
}

