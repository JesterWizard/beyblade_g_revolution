#include "global.h"

void sub_08030638(struct Unk346C0 *a, s32 b)
{
    u16 flags;
    s32 angle;
    s32 step;
    s32 x;
    s32 y;
    s32 sine;
    s32 cosine;
    s32 sine2;
    s32 cosine2;
    s32 rotated_x;
    s32 rotated_y;
    u32 index;

    flags = a->unk302;
    angle = 0;
    if ((flags & 0xC0) != 0)
    {
        step = 0x20;
        if ((flags & 0x80) != 0)
            angle = 0x80;
        else
            step = -0x20;
        if ((flags & 0x20) != 0)
            angle += step;
        if ((flags & 0x10) != 0)
            angle -= step;
    }
    else
    {
        if ((flags & 0x20) != 0)
            angle = 0xC0;
        if ((flags & 0x10) != 0)
            angle = 0x40;
    }

    index = (u8)angle;
    sine = ((s16 *)0x083C9544)[index];
    cosine = ((s16 *)0x083C9544)[index + 0x40];
    x = (b * sine) >> 8;
    y = -((b * cosine) >> 8);

    index = (u16)(-gBattleWork->unkAA8.unk14) >> 8;
    sine2 = ((s16 *)0x083C9544)[index];
    cosine2 = ((s16 *)0x083C9544)[index + 0x40];
    rotated_x = ((x * cosine2) >> 8) + ((y * sine2) >> 8);
    rotated_y = ((y * cosine2) >> 8) - ((x * sine2) >> 8);

    if ((a->unk302 & 0xF0) != 0)
    {
        gBattleWork->unk340 += rotated_x;
        gBattleWork->unk344 += rotated_y;
    }
}
