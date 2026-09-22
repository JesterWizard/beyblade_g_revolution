#include "global.h"

void sub_08034420(
    struct Unk346C0 *out_arg, struct Unk346C0Inner *state_a_arg,
    struct Unk346C0Inner *state_b, u32 mode)
{
    struct Unk346C0 *out;
    struct Unk346C0Inner *state_a;
    u32 *unk2d0;
    u8 *mode_ptr;
    s8 *bytep;
    s32 value;

    out = out_arg;
    state_a = state_a_arg;
    out->unk04 = state_b;
    out->unk00 = state_a;
out->unk19 = 0;
    out->unk18 = 0;
    out->unk2C5 = 0;
    out->unk2C8 = 0;
    out->unk2CC = 0;
    unk2d0 = &out->unk2D0;
    *unk2d0 = 0;
    out->unk2B0 = 0;
    out->unk2B4 = 0;
    out->unk2E4 = 0x10000;
    out->unk2E8 = 0x10000;
    out->unk2EC = 0;
    out->unk2F0 = 0;
    out->unk2F4 = 0;
    out->unk2F8 = -1;
    mode_ptr = &out->unk30C;
    *mode_ptr = (u8)mode;
    out->unk300 = 0;
    out->unk302 = 0;
    out->unk304 = 0;
    out->unk30E = 1;
    out->unk30D = 0;
    out->unk30F = 0;
    out->unk310 = 0;
    out->unk311 = 0;
    out->unk312 = 0;
    out->unk313 = 0;
    out->unk314 = 0;
    out->unk2B8 = 0;
    out->unk2C4 = 0;
    bytep = &state_b->unk28->unk24;
    value = *bytep;
    out->unk2C0 = value;
    sub_08067B98(
        (void *)0x0833C5AC, *mode_ptr, (s8)*(u8 *)bytep);
    if (out->unk00 != 0)
    {
        if (out->unk00->unk00 != 0)
            *unk2d0 = out->unk00->unk00->unk14 >> 12;
        out->unk2DC = state_a->unk30;
        out->unk2D8 = state_a->unk4C;
        out->unk2D4 = state_a->unk48;
        out->unk2E0 = state_a->unk34;
    }
}
