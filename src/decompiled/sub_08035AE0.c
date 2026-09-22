#include "global.h"

s32 sub_08035AE0(
    struct Unk346C0Inner *a, struct Unk346C0Inner *b)
{
    s32 result;
    s32 threshold;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 distance;
    s32 length;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 velocity_distance;
    s32 midpoint_x;
    s32 midpoint_y;
    s32 offset_x;
    s32 offset_y;
    s32 scale;

    result = 0;
    threshold = b->unk38 + a->unk38;
    dx = (b->unk0C - a->unk0C) >> 8;
    dy = (b->unk10 - a->unk10) >> 8;
    dz = (b->unk14 - a->unk14) >> 8;
    distance = dx * dx + dy * dy + dz * dz;
    scale = sub_080628B4(0x100) + 0x100;
    if (distance < threshold)
    {
        length = (u16)sub_080674B0(distance);
        dx = sub_080674A0(dx << 8, length);
        dy = sub_080674A0(dy << 8, length);
        dz = sub_080674A0(dz << 8, length);
        velocity_x = a->unk18 - b->unk18;
        velocity_y = a->unk1C - b->unk1C;
        velocity_z = a->unk20 - b->unk20;
        velocity_distance =
            velocity_x * velocity_x +
            velocity_y * velocity_y +
            velocity_z * velocity_z;
        velocity_distance = (u16)sub_080674B0(velocity_distance);
        midpoint_x = (a->unk0C + b->unk0C) >> 1;
        midpoint_y = (a->unk10 + b->unk10) >> 1;
        offset_x = dx << 4;
        offset_y = dy << 4;
        a->unk0C = midpoint_x - offset_x;
        a->unk10 = midpoint_y - offset_y;
        b->unk0C = midpoint_x + offset_x;
        b->unk10 = midpoint_y + offset_y;
        dx = (dx * velocity_distance) >> 8;
        dy = (dy * velocity_distance) >> 8;
        dz = (dz * velocity_distance) >> 8;
        a->unk18 -= (dx * a->unk34 * scale) >> 16;
        a->unk1C -= (dy * a->unk34 * scale) >> 16;
        a->unk20 -= (dz * a->unk34 * scale) >> 16;
        b->unk18 += (dx * b->unk34 * scale) >> 16;
        b->unk1C += (dy * b->unk34 * scale) >> 16;
        b->unk20 += (dz * b->unk34 * scale) >> 16;
        result = 1;
    }
    return result;
}
