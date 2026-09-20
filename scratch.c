#define sub_0807027C sub_0807027C_void_proto
#include "global.h"
#undef sub_0807027C

struct Unk70354Object *sub_0807027C(
    void *a,
    u16 b,
    u16 c,
    u8 d);

void sub_08070354(void *state_arg, u16 b, u16 c, u8 d)
{
    register struct Unk70354 *state asm("r6");
    register u16 count asm("r5");
    register u32 flags asm("r4");
    register struct Unk70354Object *object asm("r2");

    state = state_arg;
    count = c;
    flags = state->unk10;
    if (state->unk30 != 0)
    {
        object = sub_0807027C(state->unk30, b, count, d);
        state->unk30 = object;
        if (object == 0)
        {
            flags &= 0xC1FFFCFF;
            flags |= (state->unk1C & 3) << 28;
        }
    }
    else
    {
        object = sub_0807027C(0, b, count, d);
        state->unk30 = object;
        if (object != 0)
        {
            flags &= 0xC1FFFDFF;
            flags |= ((object->unk08 & 0x3E0) << 20) | 0x100;
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
