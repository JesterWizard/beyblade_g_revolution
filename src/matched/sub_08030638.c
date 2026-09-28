#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08030638
/* match-compiler: old_agbcc */
// Nudge battler A's motion by the d-pad direction in a->unk302, scaled by b
// and rotated into camera space by -unkAA8.unk14.
void sub_08030638(struct Unk346C0 *a, s32 b)
{
    struct Unk30638AA8 *cam;
    s32 angle;
    s32 step;
    s32 x, y, s, c, rx, ry;
    u8 idx;
    u32 rot;

    angle = 0;
    cam = &gData_03000290->unkAA8;
    if (a->unk302 & 0xC0)
    {
        step = 0x20;
        if (a->unk302 & 0x80)
            angle = 0x80;
        else
            step = -0x20;
        if (a->unk302 & 0x20)
            angle += step;
        if (a->unk302 & 0x10)
            angle -= step;
    }
    else
    {
        if (a->unk302 & 0x20)
            angle = 0xC0;
        if (a->unk302 & 0x10)
            angle = 0x40;
    }
    x = (b * gData_083C9544[(u8)angle]) >> 8;
    y = -(b * gData_083C9544[(u8)angle + 0x40]) >> 8;
    rot = (u32)(-cam->unk14 & 0xFFFF) >> 8;
    s = gData_083C9544[rot];
    c = gData_083C9544[rot + 0x40];
    rx = ((x * c) >> 8) + ((y * s) >> 8);
    ry = ((y * c) >> 8) - ((x * s) >> 8);
    if (a->unk302 & 0xF0)
    {
        gData_03000290->unk328.unk18 += rx;
        gData_03000290->unk328.unk1C += ry;
    }
}

