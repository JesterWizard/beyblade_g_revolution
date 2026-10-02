#include "global.h"

// @ 0x080705a4
void SpriteSetObjMode(struct Sprite *a, s32 b)
{
    u32 t;
    u32 v;
    u32 mask;

    t = b << 24;
    v = a->unk10;
    v &= 0xFFFFF3FF;
    mask = 0xC0 << 18;
    mask &= t;
    mask >>= 14;
    a->unk10 = v | mask;
}

