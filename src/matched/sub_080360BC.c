#include "global.h"

// @ 0x080360bc
#include "global.h"

// @ 0x080360bc
void sub_080360BC(struct Unk360BC *a, s32 x, s32 y, s32 scale)
{
    s32 dx;
    s32 dy;
    u16 speed;
    s32 vx;
    s32 vy;

    dx = (x - a->unk0C) >> 8;
    dy = (y - a->unk10) >> 8;
    speed = sub_080674B0(dx * dx + dy * dy);
    vx = sub_080674A0(dx << 8, speed);
    vy = sub_080674A0(dy << 8, speed);
    a->unk18 = (scale * vx) >> 8;
    a->unk1C = (scale * vy) >> 8;
}

