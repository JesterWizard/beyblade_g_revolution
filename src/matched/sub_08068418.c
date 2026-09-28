#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068418
/* match-compiler: old_agbcc */
// Per-frame object update: tick its sub-state (sub_08068798), follow its path
// or apply velocity, accelerate and damp the velocity, count down unk70 by
// the frame-clock delta, then advance its animation (sub_08068598).
void sub_08068418(void *arg)
{
    struct Unk68598 *obj = arg;
    s32 vx, vy, vz;
    s32 d, dx, dy, dz;
    s32 t;

    sub_08068798((struct Unk68798 *)obj);
    if (obj->unk80 != NULL && obj->unk84 >= 0)
        _0806D998(obj);
    if (obj->unk80 == NULL && obj->unk84 == -1)
    {
        obj->unk04 += obj->unk40;
        obj->unk08 += obj->unk44;
        obj->unk0C += obj->unk48;
    }
    vx = obj->unk40 + obj->unk4C;
    obj->unk40 = vx;
    vy = obj->unk44 + obj->unk50;
    obj->unk44 = vy;
    vz = obj->unk48 + obj->unk54;
    obj->unk48 = vz;
    d = obj->unk68;
    if (d != 0)
    {
        dx = (vx * d) >> 8;
        dy = (vy * d) >> 8;
        dz = (vz * d) >> 8;
        obj->unk40 = vx - dx;
        obj->unk44 = vy - dy;
        obj->unk48 = vz - dz;
        if (dx == 0 && obj->unk40 != 0)
            {
            if (obj->unk40 > 0)
                obj->unk40--;
            else
                obj->unk40++;
        }
        if (dy == 0 && obj->unk44 != 0)
            {
            if (obj->unk44 > 0)
                obj->unk44--;
            else
                obj->unk44++;
        }
        if (dz == 0 && obj->unk48 != 0)
            {
            if (obj->unk48 > 0)
                obj->unk48--;
            else
                obj->unk48++;
        }
    }
    if (obj->unk70 > 0)
    {
        t = obj->unk70 - (gData_03000180.unk00 - gData_03000180.unk04);
        obj->unk70 = t;
        if (t < 0)
            obj->unk70 = 0;
    }
    if (obj->unk6C == 0 && !(obj->unk98 & 1))
        sub_08068598(obj);
}

