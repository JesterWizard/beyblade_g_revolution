#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0806EE48 */
// @ 0x0806ee48
// Handler/callback dispatch plus a 4-slot motion scan. skipFollow (set by
// CameraCenterOnObject after a snap) suppresses one follow step.
void CameraUpdate(struct MapView *state)
{
    struct MapView *work;
    void *handler;
    void *callback;
    u8 i;

    work = state;
    handler = work->target;
    if (handler != 0)
    {
        if (!work->skipFollow)
        {
            callback = work->targetHandler;
            if (callback == 0)
                CameraEaseToTarget(work);
            else
                _08073C48(handler, work, callback);
        }
        else
            work->skipFollow = 0;
    }
    for (i = 0; i < 4; i++)
    {
        if (work->follow->entries[i].active != 0)
            sub_08068E54(&work->layers[i]);
    }
}

/* fn: sub_0806EEC4 */
// @ 0x0806eec4
// Returns the first motion slot of `state`, the one the camera follows.
struct MapLayer *CameraGetActive(struct MapView *state)
{
    return state->layers;
}

/* fn: sub_0806EEC8 */
// @ 0x0806eec8
/* match-compiler: old_agbcc */
// Eases the active camera halfway towards centring state->unk224, clamped to
// the map, then drags every other targeted camera by its follow ratio; each
// camera is clamped the same way.
void CameraEaseToTarget(void *arg)
{
    struct MapView *state = arg;
    struct MapLayer *cam;
    struct Actor *obj;
    s32 pos[3];
    s16 i;
    s32 y;

    cam = CameraGetActive(state);
    obj = state->target;
    SceneObjGetPosition(obj, (u32 *)pos);
    cam->deltaX = (pos[0] - (cam->offsetX + ((0x78 - (obj->width >> 1)) << 8))) >> 1;
    cam->deltaY = (pos[1] - (cam->offsetY + (((y = (s16)obj->unkA2 + 0x50) - (obj->height >> 1)) << 8))) >> 1;
    if (cam->offsetX + cam->deltaX < state->minX)
        cam->deltaX = -cam->offsetX;
    if (cam->offsetY + cam->deltaY < 0)
        cam->deltaY = -cam->offsetY;
    if (cam->offsetX + cam->deltaX > (cam->widthTiles << 11) - (state->rightMargin << 8))
        cam->deltaX = (cam->widthTiles << 11) - 0xF000 - cam->offsetX;
    if (cam->offsetY + cam->deltaY > (cam->heightTiles << 11) - 0xA000)
        cam->deltaY = (cam->heightTiles << 11) - 0xA000 - cam->offsetY;
    for (i = 0; i < 4; i++)
    {
        if (state->follow->entries[i].active != NULL)
        {
            s16 ratio = state->follow->entries[i].ratio;
            struct MapLayer *other = &state->layers[i];

            if (other != cam)
            {
                other->deltaX = cam->deltaX + ((cam->deltaX * ratio) >> 5);
                other->deltaY = cam->deltaY + ((cam->deltaY * ratio) >> 5);
                if (other->offsetX + other->deltaX < state->minX)
                    other->deltaX = -other->offsetX;
                if (other->offsetY + other->deltaY < 0)
                    other->deltaY = -other->offsetY;
                if (other->offsetX + other->deltaX > (other->widthTiles << 11) - (state->rightMargin << 8))
                    other->deltaX = (other->widthTiles << 11) - 0xF000 - other->offsetX;
                if (other->offsetY + other->deltaY > (other->heightTiles << 11) - 0xA000)
                    other->deltaY = (other->heightTiles << 11) - 0xA000 - other->offsetY;
            }
        }
    }
}

/* fn: sub_0806F05C */
// @ 0x0806f05c
/* match-compiler: old_agbcc */
// Centres the active camera on obj (clamped to the map), then moves every other
// camera that has a target by its own follow ratio (1/32 steps) of that shift.
void CameraCenterOnObject(struct MapView *state, struct Actor *obj)
{
    struct MapLayer *cam;
    s32 pos[3];
    s16 i;
    s32 y;

    cam = CameraGetActive(state);
    SceneObjGetPosition(obj, (u32 *)pos);
    state->skipFollow = 1;
    cam->deltaX = pos[0] - (cam->offsetX + ((0x78 - (obj->width >> 1)) << 8));
    cam->deltaY = pos[1] - (cam->offsetY + (((y = (s16)obj->unkA2 + 0x50) - (obj->height >> 1)) << 8));
    if (cam->offsetX + cam->deltaX < 0)
        cam->deltaX = -cam->offsetX;
    if (cam->offsetY + cam->deltaY < 0)
        cam->deltaY = -cam->offsetY;
    if (cam->offsetX + cam->deltaX > (cam->widthTiles << 11) - 0xF000)
        cam->deltaX = (cam->widthTiles << 11) - 0xF000 - cam->offsetX;
    if (cam->offsetY + cam->deltaY > (cam->heightTiles << 11) - 0xA000)
        cam->deltaY = (cam->heightTiles << 11) - 0xA000 - cam->offsetY;
    for (i = 0; i < 4; i++)
    {
        if (state->follow->entries[i].active != NULL)
        {
            s16 ratio = state->follow->entries[i].ratio;
            struct MapLayer *other = &state->layers[i];

            if (other != cam)
            {
                other->deltaX = cam->deltaX + ((cam->deltaX * ratio) >> 5);
                other->deltaY = cam->deltaY + ((cam->deltaY * ratio) >> 5);
            }
        }
    }
}

/* fn: sub_0806F174 */
// @ 0x0806f174
void CameraSetTarget(struct Unk6F174 *a, void *b)
{
    a->unk224 = b;
    if (a->unk348 == 0)
        CameraCenterOnObject((struct MapView *)a, b);
    else
        _08073C4C(b, a, (u32)a, a->unk348);
}
