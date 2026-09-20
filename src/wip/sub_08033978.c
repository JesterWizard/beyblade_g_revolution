#include "global.h"

// @ 0x08033978
void sub_08033978(
    struct Unk33A5C *out, struct Unk346C0 *state_a,
    struct Unk346C0 *state_b, u8 mode)
{
    register u32 r1;
    register u32 r0;
    register s32 minusOne;
    u32 resource_id;

    out->unk00 = 1;
    out->unk04 = state_a;
    out->unk08 = state_b;
    r1 = 0x08078158;
r0 = (u32)mode << 2;
    r0 += r1;
    r1 = *(u32 *)r0;
    sub_08034FF8((struct Unk34FF8 *)state_a, r1, (u32)state_b);
    sub_08034FF8((struct Unk34FF8 *)state_b, (u32)0x08078E58, (u32)state_a);
    sub_080330F4(0x80);
    r1 = 1;
    r1 = -r1;
    minusOne = r1;
    sub_08035204(state_a, 0, 0x0C, minusOne);
    state_a->unk08C = sub_08067FC8(&state_a->unk1C, 0);
    state_a->unk2B0 = 0;
    state_a->unk2B4 = minusOne;
    state_a->unk2CC = 2;
    state_a->unk310 = 1;
    state_b->unk2CC = 6;
    state_a->unk310 = 1;
    resource_id = mode;
    sub_08060254(0x0B, 0x38, resource_id);
    out->unk0D = 0;
}

