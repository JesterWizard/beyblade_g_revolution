#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068ec0
// Per-frame affine BG update: advance the rotation angle (wrapping at
// 0x10000) and the unk30/unk34 pair by their velocities, rebuild the BG's
// matrix (sub_08069A60) and reference point (sub_080699C8), then damp the
// velocities by unk24/256, snapping any that stop shrinking to zero.
void AffineBgUpdate(void *arg)
{
    struct Unk68E54 *st = arg;
    u8 slot;
    s32 angle;
    s32 x, y;
    s32 damp;
    s32 dA, dX, dY;

    slot = st->unk5E - 2;
    angle = st->unk28 + st->unk2C;
    st->unk28 = angle;
    if (angle < 0)
        st->unk28 = angle + 0x10000;
    x = st->unk30 + st->unk38;
    st->unk30 = x;
    y = st->unk34 + st->unk3C;
    st->unk34 = y;
    sub_08069A60(st->unk5E, (u8)(st->unk28 >> 8), (u16)(x >> 8), (u16)(y >> 8));
    BgAffineSetRefPoint(st->unk5E,
                 st->unk4C - (gData_03000068[slot].unk08 * st->unk48 - gData_03000068[slot].unk10 * st->unk4A),
                 st->unk50 + (st->unk48 * gData_03000068[slot].unk0C - gData_03000068[slot].unk14 * st->unk4A));
    damp = st->unk24;
    if (damp != 0)
    {
        dA = (st->unk2C * damp) >> 8;
        dX = (st->unk38 * damp) >> 8;
        dY = (st->unk3C * damp) >> 8;
        st->unk2C -= dA;
        st->unk38 -= dX;
        st->unk3C -= dY;
        if (dA == 0 && st->unk2C != 0)
            st->unk2C = 0;
        if (dX == 0 && st->unk38 != 0)
            st->unk38 = 0;
        if (dY == 0 && st->unk3C != 0)
            st->unk3C = 0;
    }
}

