#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08070354
/* match-compiler: old_agbcc */
#include "global.h"

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
        object = state->unk30 = sub_0807027C(object, b, count, mode);
        if (object == 0)
        {
            flags &= 0xC1FFFCFF;
            flags |= (u32)(state->unk1C & 3) << 28;
        }
    }
    else
    {
        object = state->unk30 = sub_0807027C(0, b, count, mode);
        if (object != 0)
        {
            flags &= 0xC1FFFDFF;
            value = object->unk08 & (0xF8 << 2);
            value <<= 20;
            value |= 0x80 << 1;
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

