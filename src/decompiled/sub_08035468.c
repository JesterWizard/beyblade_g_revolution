#include "global.h"

struct Unk35468Output
{
    u8 filler_00[8];
    s32 unk08;
    s32 unk0C;
};

struct Unk35468Source
{
    u8 filler_00[0xB8];
    struct Unk35468Output *unkB8;
};

void sub_08035468(
    void *source_arg, s32 x, s32 y, s32 z,
    s32 x_scale, s32 y_scale, s32 angle)
{
    struct Unk35468Source *source;
    struct Unk35468Output *output;
    struct Unk30638AA8 *root;
    s16 *table;
    s32 index;
    s32 sine;
    s32 cosine;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 rotated_x;
    s32 rotated_y;
    s32 correction;
    s32 second_sine;
    s32 second_cosine;
    s32 scale_x;
    s32 scale_y;
    s32 diff_angle;

    source = (struct Unk35468Source *)source_arg;
    output = source->unkB8;
    root = &gBattleWork->unkAA8;
    if (output == 0)
        return;
    table = (s16 *)0x083C9544;
    index = ((root->unk14 & 0xFFFF) >> 8);
    sine = table[index];
    cosine = table[index + 0x40];
    dx = x - root->unk00;
    dy = y - root->unk04;
    dz = (z - root->unk08) >> 8;
    dx = (dx * dz) >> 8;
    dy = (dy * dz) >> 8;
    rotated_x = ((dx * cosine) >> 8) + ((dy * sine) >> 8);
    rotated_x += root->unk0C;
    rotated_y = ((dy * cosine) >> 8) - ((dx * sine) >> 8);
    rotated_y += root->unk10;
    correction = (dz << 13) >> 8;
    rotated_x -= correction;
    rotated_y -= correction;
    if (dz <= 0xFF)
    {
        correction = ((0x100 - dz) << 13) >> 8;
        rotated_x -= correction;
        rotated_y -= correction;
    }
    diff_angle = root->unk14 - angle;
    index = ((diff_angle & 0xFFFF) >> 8);
    second_sine = table[index];
    second_cosine = table[index + 0x40];
    scale_x = ((x_scale * second_cosine) >> 8) +
        ((y_scale * second_sine) >> 8);
    scale_y = ((y_scale * second_cosine) >> 8) -
        ((x_scale * second_sine) >> 8);
    rotated_x -= (scale_x * dz) >> 8;
    rotated_y -= (scale_y * dz) >> 8;
    output->unk08 = rotated_x;
    output->unk0C = rotated_y;
    diff_angle = (angle - root->unk14) >> 8;
    sub_08070354(
        output, (u16)dz, (u16)dz, (u8)diff_angle);
}
