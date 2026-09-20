#include "global.h"

u32 sub_080691E4(
    struct Unk691E4 *a,
    u32 value_arg,
    u32 flags_arg)
{
    register struct Unk691E4 *state asm("r3");
    register u32 value asm("r1");
    register u32 flags asm("r2");
    register u32 result asm("r4");
    register u32 one asm("r5");

    state = a;
    value = value_arg << 16;
    flags = (u16)flags_arg;
    value >>= 30;
    one = 1;
    if ((flags & one) != 0)
    {
        result = one << ((value << 1) + 8);
        value += 4;
        state->unk5F = value;
        state->unk60 = value;
    }
    else
    {
        switch (value)
        {
        case 0:
            result = 0x800;
            state->unk5F = 5;
            state->unk60 = 5;
            break;
        case 1:
            result = 0x1000;
            state->unk5F = 6;
            state->unk60 = 5;
            break;
        case 2:
            result = 0x1000;
            state->unk5F = 5;
            state->unk60 = 6;
            break;
        case 3:
            result = 0x2000;
            state->unk5F = 6;
            state->unk60 = 6;
            break;
        }
    }
    return result;
}
