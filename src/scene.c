#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0804188C */
// @ 0x0804188c
/* match-compiler: old_agbcc */
// Per-frame update of the scene objects: tick each one, refresh its sort key
// (0xFFFF when unkD8 == 1, else ~(unk08 >> 8)) and re-claim its palette slot.
void SceneObjsUpdateAll(void)
{
    s16 i;
    u16 color;

    i = 0;
    if (gData_03000504 > 0)
    {
        ObjPaletteSlotsReleaseRange(3, 0x0F);
        while (i < gData_03000504)
        {
            SceneObjUpdate(gData_03000480[i]);
            if (gData_03000480[i]->unkB8 != NULL)
            {
                if (gData_03000480[i]->unkD8 == (void *)1)
                {
                    gData_03000480[i]->unkBC = 0xFFFF;
                    BtlObjListResort(gData_03000480[i]->unkB8, gData_03000480[i]->unkBC);
                }
                else
                {
                    gData_03000480[i]->unkBC = ~((s32)gData_03000480[i]->y >> 8);
                    BtlObjListResort(gData_03000480[i]->unkB8, gData_03000480[i]->unkBC);
                }
                if (gData_03000480[i]->unkD8 == NULL)
                    color = (s8)ScenePaletteAcquire(gData_080775CC, gData_03000480[i]->unkD4);
                else
                    color = (s8)ScenePaletteAcquire(gData_080779A8, gData_03000480[i]->unkD4);
                gData_03000480[i]->unk3A = (color << 1) | 1;
            }
            sub_08067CE8((struct AnimObj *)gData_03000480[i++], 0);
        }
    }
}

/* fn: sub_080419B0 */
// @ 0x080419b0
// Take the next free object from the gData_03000534 pool (at most 0x20 live),
// initialise it through sub_08067BB8, and append it to the gData_03000480
// list (kept NULL-terminated).
struct Actor *SceneObjSpawn(u32 a, u32 b, u32 c, u32 d)
{
    if (gData_03000534 == NULL || gData_03000504 > 0x1F)
        return NULL;
    AnimObjCreate((struct AnimObj *)&gData_03000534[gData_03000504], (struct Unk67BB8Source *)b, a, c, d, 0, -1);
    gData_03000534[gData_03000504].unkBC = ~d;
    gData_03000480[gData_03000504] = &gData_03000534[gData_03000504];
    gData_03000480[gData_03000504 + 1] = NULL;
    return &gData_03000534[gData_03000504++];
}

/* fn: sub_08041B74 */
// @ 0x08041b74
/* match-compiler: old_agbcc */
// Remove the live object bound to (a, b): free its unkC8 node, park it
// off-screen, and swap the last slot into its place.
void SceneObjDespawn(void *a, void *b)
{
    s16 i;
    struct Actor **slot;

    i = 0;
    if (gData_03000504 > 0)
    {
        for (; i < gData_03000504; i++)
        {
            slot = &gData_03000480[i];
            if (*slot != NULL && (*slot)->unkD4 == a && (*slot)->unkD8 == b)
            {
                if ((*slot)->unkC8 != NULL)
                {
                    TaskDestroy((struct Unk59D08 *)(*slot)->unkC8);
                    (*slot)->unkC8 = NULL;
                }
                SceneObjFreeResources(*slot);
                (*slot)->x = -0x4000;
                (*slot)->y = -0x4000;
                *slot = gData_03000480[--gData_03000504];
                gData_03000480[gData_03000504] = NULL;
                return;
            }
        }
    }
}

/* fn: sub_080447E8 */
// @ 0x080447e8
/* match-compiler: old_agbcc */
// Walks a -1-terminated id list and spawns a scene object for each kind-1
// entry of the 0x0807BE04 table, or parks the two position records of kind 2.
void SceneObjSpawnList(void *arg)
{
    s32 *ids = arg;
    struct Unk6DEF4 *records;
    struct MapView *state;
    s32 id;
    s32 *pos;
    struct Actor *obj;
    struct Unk7BE04 *def;
    struct Unk7BE04 *def2;
    struct Unk7BE04 *tbl;
    struct Unk7BE04 *tbl2;
    struct Unk59C98Src *part;

    records = (struct Unk6DEF4 *)sub_08062A14();
    state = (struct MapView *)CameraGetActive((struct MapView *)gData_03000198);
    while (*ids != -1)
    {
        id = *ids;
        if (sub_0803EDF0(id) == 1)
        {
            tbl = gData_0807BE04;
            def = &tbl[id];
            pos = (s32 *)PosRecordGet(records, def->unk02);
            if (pos != NULL)
            {
                obj = SceneObjSpawn((u32)state, (u32)gData_0807BE04[id].unk10, pos[0] >> 3, pos[1] >> 3);
                obj->unkD4 = (void *)id;
                obj->unkD8 = NULL;
                if (obj != NULL)
                {
                    obj->y -= obj->height << 8;
                    obj->x -= (obj->width >> 1) << 8;
                    if (gData_0807BE04[id].unk08 != NULL)
                    {
                        obj->unkC4 = gData_0807BE04[id].unk08;
                        sub_080626B8((struct Unk626B8 *)&gData_03000198->unk0524, (u32)obj);
                        obj->unkCC = 0x10;
                        obj->unkD0 = 0x10;
                    }
                    part = gData_0807BE04[id].unk0C;
                    if (part != NULL)
                    {
                        TaskCreateWithOwner(part, (struct Unk59C98Owner *)obj, def, (void *)sub_0803EDC8(id));
                        if (gData_0807BE04[id].unk18 >= 0)
                            obj->unk3B = gData_0807BE04[id].unk18;
                    }
                    else
                        obj->unkC8 = (void *)part;
                }
            }
        }
        else if (sub_0803EDF0(id) == 2)
        {
            tbl2 = gData_0807BE04;
            def2 = &tbl2[id];
            pos = (s32 *)PosRecordGet(records, def2->unk02);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
            pos = (s32 *)PosRecordGet(records, def2->unk02 + 1);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
        }
        ids++;
    }
}

/* fn: sub_0804DB28 */
// @ 0x0804db28
/* match-compiler: old_agbcc */
// Rebuild the object pool for scene gData_03000694: reset all nine
// objects, lay out eight in a 4x2 grid from the scene's gData_0807BE04 source,
// load their palette, pick each one's animation, and set up the optional ninth
// object when the scene has one (otherwise park it off-screen).
void SceneObjPoolRebuild(void)
{
    s32 i;

    for (i = 0; i < 9; i++)
        SceneObjFreeResources(&gData_03000698[i]);

    AnimObjCreate((struct AnimObj *)&gData_03000698[0], gData_0807BE04[gData_03000694].unk10, 0, 0x32, 0x34, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[1], gData_0807BE04[gData_03000694].unk10, 0, 0x5A, 0x34, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[2], gData_0807BE04[gData_03000694].unk10, 0, 0x82, 0x34, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[3], gData_0807BE04[gData_03000694].unk10, 0, 0xAA, 0x34, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[4], gData_0807BE04[gData_03000694].unk10, 0, 0x32, 0x6C, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[5], gData_0807BE04[gData_03000694].unk10, 0, 0x5A, 0x6C, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[6], gData_0807BE04[gData_03000694].unk10, 0, 0x82, 0x6C, 0, -1);
    AnimObjCreate((struct AnimObj *)&gData_03000698[7], gData_0807BE04[gData_03000694].unk10, 0, 0xAA, 0x6C, 0, -1);

    gData_03000698[0].unk3A = 0x1F;
    gData_03000698[1].unk3A = 0x1F;
    gData_03000698[2].unk3A = 0x1F;
    gData_03000698[3].unk3A = 0x1F;
    gData_03000698[4].unk3A = 0x1F;
    gData_03000698[5].unk3A = 0x1F;
    gData_03000698[6].unk3A = 0x1F;
    gData_03000698[7].unk3A = 0x1F;

    _08073C4C(gData_080775CC[gData_03000694], (void *)0x050003E0, 0x20, (void *)gData_080BB8C0[0]);

    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[0], 5);
    gData_03000698[0].unk31 &= 2;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[1], 5);
    gData_03000698[1].unk31 |= 1;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[2], 6);
    gData_03000698[2].unk31 = 0;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[3], 7);
    gData_03000698[3].unk31 = 0;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[4], 8);
    gData_03000698[4].unk31 &= 2;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[5], 8);
    gData_03000698[5].unk31 |= 1;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[6], 10);
    gData_03000698[6].unk31 = 0;
    AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gData_03000698[7], 11);
    gData_03000698[7].unk31 = 0;

    sub_08054558(gData_08098A20[gData_03000694]);

    if (gData_08098DF8[gData_03000694] != NULL && gData_080991D0[gData_03000694] != NULL)
    {
        AnimObjCreate((struct AnimObj *)&gData_03000698[8], gData_080991D0[gData_03000694], 0, 0x8C, 3, 0, -1);
        _08073C4C(gData_08098DF8[gData_03000694], (void *)0x050003C0, 0x20, (void *)gData_080BB8C0[0]);
        gData_03000698[8].unk3A = 0x1D;
    }
    else
    {
        gData_03000698[8].x = -0x4000;
        gData_03000698[8].y = -0x4000;
    }

    for (i = 0; i <= 8; i++)
    {
        if (gData_03000698[i].unk00 != NULL)
        {
            SceneObjUpdate(&gData_03000698[i]);
            sub_08067CE8((struct AnimObj *)&gData_03000698[i], 0);
        }
    }
}

/* fn: sub_0806225C */
// @ 0x0806225c

void SceneObjMotionStep(struct SceneObjSprite *a)
{
    struct Sprite *target;

    if (a == 0)
        return;
    a->posX += a->velX;
    a->posY += a->velY;
    a->velX += a->accelX;
    a->velY += a->accelY;
    if (a->velX != 0)
    {
        if (a->velX > 0)
            a->velX -= a->drag;
        if (a->velX < 0)
            a->velX += a->drag;
    }
    if (a->velY != 0)
    {
        if (a->velY > 0)
            a->velY -= a->drag;
        if (a->velY < 0)
            a->velY += a->drag;
    }
    if (a->anchor != 0)
    {
        target = a->sprite;
        if (target != 0)
        {
            target->unk08 = a->posX - a->anchor->originX;
            target->unk0C = a->posY - a->anchor->originY;
            TextEntrySetPaletteBank(target, a->paletteBank);
        }
    }
    else
    {
        target = a->sprite;
        if (target != 0)
        {
            target->unk08 = a->posX;
            target->unk0C = a->posY;
            TextEntrySetPaletteBank(target, a->paletteBank);
        }
    }
    if (a->frames != 0)
        sub_08062358(a);
    if (a->unk18 != 0)
        sub_08062640((struct SceneObjSprite *)a);
}

/* fn: sub_08068418 */
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

/* fn: sub_080686B4 */
// @ 0x080686b4
void SceneObjGetPosition(struct Actor *a, u32 *b)
{
    if (a->positionFn != 0)
        _08073C4C(a, b, (u32)a, a->positionFn);
    else
    {
        b[0] = a->x;
        b[1] = a->y;
        b[2] = a->z;
    }
}

/* fn: sub_08068808 */
// @ 0x08068808
void SceneObjFreeResources(struct Actor *a)
{
    if (a->unkB8 != 0)
    {
        BtlObjPoolFree(a->unkB8);
        a->unkB8 = 0;
    }
    if (a->unk7C != 0)
        HeapFree(a->unk7C);
    a->unk74 = -1;
    a->unk78 = 0;
    a->unk7C = 0;
}
