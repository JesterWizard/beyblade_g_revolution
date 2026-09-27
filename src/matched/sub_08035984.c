#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035984
// Per-frame motion step: heading byte from the velocity angle, clamp velocity,
// integrate position/velocity/accel, apply damping, advance the sine wobble.
void sub_08035984(struct Unk35984 *a)
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

    vx = a->unk18;
    vy = a->unk1C;
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
    a->unk52 = table_value;
    if (a->unk18 > 0)
        a->unk52 = 0xFF - table_value;

    if (a->unk18 > 0x1000)
        a->unk18 = 0x1000;
    if (a->unk18 < -0x1000)
        a->unk18 = -0x1000;
    if (a->unk1C > 0x1000)
        a->unk1C = 0x1000;
    if (a->unk1C < -0x1000)
        a->unk1C = -0x1000;

    a->unk0C += a->unk18;
    a->unk10 += a->unk1C;
    a->unk14 += a->unk20;
    a->unk18 += a->unk24;
    a->unk1C += a->unk28;
    a->unk20 += a->unk2C;

    factor = a->unk30;
    x = (a->unk18 * factor) >> 8;
    y = (a->unk1C * factor) >> 8;
    z = (a->unk20 * factor) >> 8;
    if (factor != 0)
    {
        if (x != 0)
            a->unk18 -= x;
        else if (a->unk18 != 0)
        {
            if (a->unk18 > 0)
                a->unk18--;
            else
                a->unk18++;
        }
        if (y != 0)
            a->unk1C -= y;
        else if (a->unk1C != 0)
        {
            if (a->unk1C > 0)
                a->unk1C--;
            else
                a->unk1C++;
        }
        if (z != 0)
            a->unk20 -= z;
        else if (a->unk20 != 0)
        {
            if (a->unk20 > 0)
                a->unk20--;
            else
                a->unk20++;
        }
    }

    idx = (a->unk44 + a->unk48) & 0xFFFF;
    a->unk44 = idx;
    sn = gData_083C9544[idx >> 8];
    cs = gData_083C9544[(idx >> 8) + 0x40];
    a->unk3C = (sn * a->unk4C) >> 8;
    a->unk40 = (cs * a->unk4C) >> 8;
}

