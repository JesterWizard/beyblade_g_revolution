#include "global.h"
#include "ram_map.h"
#include "battle.h"

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

