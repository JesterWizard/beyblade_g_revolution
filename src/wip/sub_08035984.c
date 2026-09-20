#include "global.h"

void sub_08035984(struct Unk35984 *a)
{
    s32 speed;
    s32 speed16;
    s32 angle;
    s32 half;
    s32 table_value;
    s32 factor;
    s32 x;
    s32 y;
    s32 z;
    s32 index;
    const u8 *table8;
    const s16 *table16;

    speed = sub_080674B0(a->unk18 * a->unk18 + a->unk1C * a->unk1C);
    speed16 = (u16)speed;
    angle = sub_080674A0(a->unk1C << 8, speed16);
    half = angle >> 1;
    if (half > 0x7F)
        half = 0x7F;
    if (half < -0x80)
        half = -0x80;
    table8 = (const u8 *)0x083C97C4;
    table_value = table8[(s8)half + 0x80];
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

    a->unk44 = (a->unk44 + a->unk48) & 0xFFFF;
    table16 = (const s16 *)0x083C9544;
    index = a->unk44 >> 8;
    a->unk3C = (table16[index] * a->unk4C) >> 8;
    a->unk40 = (table16[index + 0x40] * a->unk4C) >> 8;
}
