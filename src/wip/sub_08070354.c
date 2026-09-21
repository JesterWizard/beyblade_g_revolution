/* match-compiler: old_agbcc */
#define sub_08070354 sub_08070354_void_proto
#define sub_0807027C sub_0807027C_void_proto
#include "global.h"
#undef sub_08070354
#undef sub_0807027C

struct Unk70354Object *sub_0807027C(
    void *a,
    u16 b,
    u16 c,
    u8 d);

void sub_08070354(struct Unk70354 *state, u16 b, u16 c, u8 d)
{
    u16 count = (u16)c;
    u8 mode = d;
    u32 flags;
    struct Unk70354Object *object;
    u32 value;

    object = state->unk30;
    flags = state->unk10;
    if (object != 0)
    {
        object = sub_0807027C(object, b, count, mode);
        state->unk30 = object;
        if (object == 0)
        {
            flags &= 0xC1FFFCFF;
            value = (state->unk1C & 3) << 28;
            flags |= value;
        }
    }
    else
    {
        object = sub_0807027C(0, b, count, mode);
        state->unk30 = object;
        if (object != 0)
        {
            flags &= 0xC1FFFDFF;
            value = (object->unk08 & 0x3E0) << 20;
            value |= 0x100;
            flags |= value;
        }
    }
    if (object != 0)
    {
        if (object->unk18 != 0)
        {
            if (object->unk14 > 0xB0 || object->unk16 > 0xB0)
                flags |= 0x200;
            else
                flags &= 0xFFFFFDFF;
        }
        else
        {
            if (object->unk14 > 0x100 || object->unk16 > 0x100)
                flags |= 0x200;
            else
                flags &= 0xFFFFFDFF;
        }
    }
    state->unk10 = flags;
}
