#include "global.h"

// @ 0x08035c64
u8 sub_08035C64(struct Unk346C0Inner *a, s32 x, s32 y, s32 z, s32 threshold)
{
    s32 dx;
    s32 dy;
    s32 distSq;
    s32 sumSq;
    s32 randScale;
    u16 speed;
    s32 vx;
    s32 vy;
    u16 curSpeed;
    s32 scale;

    dx = (x - a->unk0C) >> 8;
    dy = (y - a->unk10) >> 8;
    distSq = z * z - a->unk38;
    sumSq = dx * dx + dy * dy;
    randScale = RandRange(0x80) + 0x100;

    if (sumSq > distSq)
    {
        if (a->unk14 < threshold)
        {
            a->unk2C = 0;
            a->unk20 = 0;
            a->unk1C = 0;
            a->unk18 = 0;
            return 0;
        }
        else
        {
            speed = Sqrt(sumSq);
            vx = Div(dx << 8, speed);
            vy = Div(dy << 8, speed);
            curSpeed = Sqrt(a->unk18 * a->unk18 + a->unk1C * a->unk1C);
            scale = (randScale * curSpeed) >> 8;
            vx = (vx * scale) >> 8;
            vy = (vy * scale) >> 8;
            a->unk18 += vx;
            a->unk1C += vy;
        }
    }
    return 1;
}
