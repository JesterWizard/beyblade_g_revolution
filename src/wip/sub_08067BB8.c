#include "global.h"

void sub_08067BB8(
    struct Unk67BB8 *state,
    struct Unk67BB8Source *source,
    u32 arg2,
    u32 arg3,
    u32 arg4,
    u32 arg5,
    u32 arg6)
{
    register u32 zero asm("r4");
    register u32 byte_zero asm("r5");
    register u32 allones asm("r2");

    state->unk00 = source;
    state->unk58 = gUnk_03000180.unk00;
    state->unk3C = arg2;
    state->unk70 = arg6;
    state->unk04 = arg3 << 8;
    state->unk08 = arg4 << 8;
    state->unk0C = arg5 << 8;
    zero = 0;
    byte_zero = 0;
    allones = 0xFFFF;
    state->unk16 = zero;
    state->unk12 = 0x100;
    state->unk14 = 0x100;
    state->unkA0 = zero;
    state->unkA2 = zero;
    state->unkA4 = byte_zero;
    state->unkA5 = byte_zero;
    state->unk40 = zero;
    state->unk44 = zero;
    state->unk48 = zero;
    state->unk4C = zero;
    state->unk50 = zero;
    state->unk54 = zero;
    state->unk68 = 0x10;
    state->unk18 = zero;
    state->unk64 = zero;
    state->unk22 = zero;
    state->unk60 |= allones;
    state->unk1A |= allones;
    state->unk1C = zero;
    state->unk1E = zero;
    state->unk20 = zero;
    state->unk2C = zero;
    state->unk2E |= allones;
    state->unk10 = source->unk04;
    state->unk11 = source->unk05;
    state->unk30 = source->unk06;
    state->unk2A = source->unk08;
    state->unk38 = source->unk07;
    state->unk28 = source->unk14;
    state->unk31 = byte_zero;
    state->unk39 = byte_zero;
    state->unk3B = byte_zero;
    state->unk3A = source->unk0C;
    state->unk6C = zero;
    state->unk74 = -1;
    state->unk78 = zero;
    state->unk7C = zero;
    state->unk80 = zero;
    state->unk84 = -1;
    state->unk88 = zero;
    state->unk8C = byte_zero;
    state->unk8D = byte_zero;
    state->unk98 = byte_zero;
    state->unk90 = zero;
    state->unk94 = zero;
    sub_08068574(
        (struct Unk68574 *)state,
        state->unk10 >> 1,
        state->unk11,
        zero);
    sub_08068558(
        (struct Unk68574 *)state,
        zero,
        zero,
        state->unk10,
        state->unk11);
    state->unkB8 = zero;
    state->unkBC = zero;
    sub_08068180((struct Unk680CC *)state, zero);
    state->unkC0 = zero;
}
