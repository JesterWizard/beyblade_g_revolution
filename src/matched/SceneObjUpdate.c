#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08068418
/* match-compiler: old_agbcc */
// Per-frame object update: tick its sub-state (sub_08068798), follow its path
// or apply velocity, accelerate and damp the velocity, count down unk70 by
// the frame-clock delta, then advance its animation (sub_08068598).
void SceneObjUpdate(void *arg)
{
    struct AnimObjPlayback *obj = arg;
    s32 vx, vy, vz;
    s32 d, dx, dy, dz;
    s32 t;

    ActorApplyMotionModifiers((struct Unk68798 *)obj);
    if (obj->path != NULL && obj->pathStep >= 0)
        _0806D998(obj);
    if (obj->path == NULL && obj->pathStep == -1)
    {
        obj->x += obj->velX;
        obj->y += obj->velY;
        obj->z += obj->velZ;
    }
    vx = obj->velX + obj->accelX;
    obj->velX = vx;
    vy = obj->velY + obj->accelY;
    obj->velY = vy;
    vz = obj->velZ + obj->accelZ;
    obj->velZ = vz;
    d = obj->damping;
    if (d != 0)
    {
        dx = (vx * d) >> 8;
        dy = (vy * d) >> 8;
        dz = (vz * d) >> 8;
        obj->velX = vx - dx;
        obj->velY = vy - dy;
        obj->velZ = vz - dz;
        if (dx == 0 && obj->velX != 0)
            {
            if (obj->velX > 0)
                obj->velX--;
            else
                obj->velX++;
        }
        if (dy == 0 && obj->velY != 0)
            {
            if (obj->velY > 0)
                obj->velY--;
            else
                obj->velY++;
        }
        if (dz == 0 && obj->velZ != 0)
            {
            if (obj->velZ > 0)
                obj->velZ--;
            else
                obj->velZ++;
        }
    }
    if (obj->countdown > 0)
    {
        t = obj->countdown - (gData_03000180.unk00 - gData_03000180.unk04);
        obj->countdown = t;
        if (t < 0)
            obj->countdown = 0;
    }
    if (obj->animHold == 0 && !(obj->flags & 1))
        AnimAdvanceFrame(obj);
}

