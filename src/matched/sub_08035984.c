#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035984
// Per-frame motion step: heading byte from the velocity angle, clamp velocity,
// integrate position/velocity/accel, apply damping, advance the sine wobble.
void BeybladeMotionStep(struct BeybladeBody *a)
{
    s32 speed;
    s32 sn;
    s32 cs;
    u32 idx;
    s32 vx;
    s32 vy;
    s32 speed16;
    s32 half;
    s32 table_value;
    s32 factor;
    s32 x;
    s32 y;
    s32 z;
    s32 index;
    const u8 *table8;

    vx = a->velX;
    vy = a->velY;
    speed = Sqrt(vx * vx + vy * vy);
    speed16 = (u16)speed;
    vy = Div(vy << 8, speed16); // vy now holds the angle
    half = vy >> 1;
    if (half > 0x7F)
        half = 0x7F;
    if (half < -0x80)
        half = -0x80;
    table8 = gData_083C97C4;
    index = (s8)half + 0x80;
    table_value = table8[index];
    a->heading = table_value;
    if (a->velX > 0)
        a->heading = 0xFF - table_value;

    if (a->velX > 0x1000)
        a->velX = 0x1000;
    if (a->velX < -0x1000)
        a->velX = -0x1000;
    if (a->velY > 0x1000)
        a->velY = 0x1000;
    if (a->velY < -0x1000)
        a->velY = -0x1000;

    a->posX += a->velX;
    a->posY += a->velY;
    a->posZ += a->velZ;
    a->velX += a->accelX;
    a->velY += a->accelY;
    a->velZ += a->accelZ;

    factor = a->drag;
    x = (a->velX * factor) >> 8;
    y = (a->velY * factor) >> 8;
    z = (a->velZ * factor) >> 8;
    if (factor != 0)
    {
        if (x != 0)
            a->velX -= x;
        else if (a->velX != 0)
        {
            if (a->velX > 0)
                a->velX--;
            else
                a->velX++;
        }
        if (y != 0)
            a->velY -= y;
        else if (a->velY != 0)
        {
            if (a->velY > 0)
                a->velY--;
            else
                a->velY++;
        }
        if (z != 0)
            a->velZ -= z;
        else if (a->velZ != 0)
        {
            if (a->velZ > 0)
                a->velZ--;
            else
                a->velZ++;
        }
    }

    idx = (a->wobblePhase + a->wobbleSpeed) & 0xFFFF;
    a->wobblePhase = idx;
    sn = gData_083C9544[idx >> 8];
    cs = gData_083C9544[(idx >> 8) + 0x40];
    a->wobbleX = (sn * a->wobbleAmp) >> 8;
    a->wobbleY = (cs * a->wobbleAmp) >> 8;
}

