#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035ae0
// Sphere overlap response between two motion objects: if closer than the summed
// radii, push both apart along the contact normal and exchange velocity scaled
// by each mass (unk34) and a random 1.0-2.0 factor. Returns 1 on contact.
// (The do/while(0) scope around the setup is needed for register allocation.)
s32 BeybladeCollisionResponse(
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

    do
    {
        result = 0;
        threshold = a->unk38 + b->unk38;
    } while (0);
    dx = (b->unk0C - a->unk0C) >> 8;
    dy = (b->unk10 - a->unk10) >> 8;
    dz = (b->unk14 - a->unk14) >> 8;
    distance = dx * dx + dy * dy + dz * dz;
    scale = RandRange(0x100) + 0x100;
    if (distance < threshold)
    {
        length = (u16)Sqrt(distance);
        dx = Div(dx << 8, length);
        dy = Div(dy << 8, length);
        dz = Div(dz << 8, length);
        velocity_x = a->unk18 - b->unk18;
        velocity_y = a->unk1C - b->unk1C;
        velocity_z = a->unk20 - b->unk20;
        velocity_distance = (u16)Sqrt(velocity_x * velocity_x + velocity_y * velocity_y + velocity_z * velocity_z);
        midpoint_x = (a->unk0C + b->unk0C) >> 1;
        midpoint_y = (a->unk10 + b->unk10) >> 1;
        a->unk0C = midpoint_x - (dx << 4);
        a->unk10 = midpoint_y - (dy << 4);
        b->unk0C = midpoint_x + (dx << 4);
        b->unk10 = midpoint_y + (dy << 4);
        dx = (dx * velocity_distance) >> 8;
        dy = (dy * velocity_distance) >> 8;
        dz = (dz * velocity_distance) >> 8;
        a->unk18 -= (dx * (s32)a->unk34 * scale) >> 16;
        a->unk1C -= (dy * (s32)a->unk34 * scale) >> 16;
        a->unk20 -= (dz * (s32)a->unk34 * scale) >> 16;
        b->unk18 += (dx * (s32)b->unk34 * scale) >> 16;
        b->unk1C += (dy * (s32)b->unk34 * scale) >> 16;
        b->unk20 += (dz * (s32)b->unk34 * scale) >> 16;
        result = 1;
    }
    return result;
}

