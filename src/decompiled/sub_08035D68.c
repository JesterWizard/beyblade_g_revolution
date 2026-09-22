#include "global.h"

struct Unk35D68Output;

struct Unk35D68Source
{
    struct Unk35D68Output *unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
};

struct Unk35D68Output
{
    u8 filler_00[8];
    s32 unk08;
    s32 unk0C;
    u8 filler_10[0x20];
    struct Unk70354Object *unk30;
};

struct Unk35D68State
{
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    u16 unk14;
};

void sub_08035D68(void *source_arg, struct Unk35D68State *state)
{
    struct Unk35D68Source *source;
    struct Unk35D68Output *output;
    s16 *table;
    s32 index;
    s32 sine;
    s32 cosine;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 out_x;
    s32 out_y;
    u8 flag;

    source = (struct Unk35D68Source *)source_arg;
    flag = 0;
    table = (s16 *)0x083C9544;
    index = state->unk14 >> 8;
    sine = table[index];
    cosine = table[index + 0x40];
    dx = source->unk0C - state->unk00;
    dy = source->unk10 - state->unk04;
    dz = (source->unk14 - state->unk08) >> 8;
    dx = (dx * dz) >> 8;
    dy = (dy * dz) >> 8;
    out_x = ((dx * cosine) >> 8) + ((dy * sine) >> 8);
    out_x += state->unk0C;
    out_x -= source->unk04;
    out_y = ((dy * cosine) >> 8) - ((dx * sine) >> 8);
    out_y += state->unk10;
    out_y -= source->unk08;
    if (dz > 0x100)
    {
        out_x -= ((dz - 0x100) * source->unk04) >> 8;
        out_y -= ((dz - 0x100) * source->unk08) >> 8;
    }
    output = source->unk00;
    output->unk08 = out_x;
    output->unk0C = out_y;
    if (output->unk30 != 0)
        flag = output->unk30->unk18;
    sub_08070354(output, (u16)dz, (u16)dz, flag);
}
