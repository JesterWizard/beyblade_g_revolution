#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806eec8
/* match-compiler: old_agbcc */
// Eases the active camera halfway towards centring state->unk224, clamped to
// the map, then drags every other targeted camera by its follow ratio; each
// camera is clamped the same way.
void CameraEaseToTarget(void *arg)
{
    struct Unk6EE48 *state = arg;
    struct Unk68E54 *cam;
    struct Unk68574 *obj;
    s32 pos[3];
    s16 i;
    s32 y;

    cam = CameraGetActive(state);
    obj = state->unk224;
    SceneObjGetPosition(obj, (u32 *)pos);
    cam->unk14 = (pos[0] - (cam->unk40 + ((0x78 - (obj->unk10 >> 1)) << 8))) >> 1;
    cam->unk18 = (pos[1] - (cam->unk44 + (((y = (s16)obj->unkA2 + 0x50) - (obj->unk11 >> 1)) << 8))) >> 1;
    if (cam->unk40 + cam->unk14 < state->unk35C)
        cam->unk14 = -cam->unk40;
    if (cam->unk44 + cam->unk18 < 0)
        cam->unk18 = -cam->unk44;
    if (cam->unk40 + cam->unk14 > (cam->unk00 << 11) - (state->unk360 << 8))
        cam->unk14 = (cam->unk00 << 11) - 0xF000 - cam->unk40;
    if (cam->unk44 + cam->unk18 > (cam->unk04 << 11) - 0xA000)
        cam->unk18 = (cam->unk04 << 11) - 0xA000 - cam->unk44;
    for (i = 0; i < 4; i++)
    {
        if (state->unk220->entries[i].unk00 != NULL)
        {
            s16 ratio = state->unk220->entries[i].unk14;
            struct Unk68E54 *other = &state->motion[i];

            if (other != cam)
            {
                other->unk14 = cam->unk14 + ((cam->unk14 * ratio) >> 5);
                other->unk18 = cam->unk18 + ((cam->unk18 * ratio) >> 5);
                if (other->unk40 + other->unk14 < state->unk35C)
                    other->unk14 = -other->unk40;
                if (other->unk44 + other->unk18 < 0)
                    other->unk18 = -other->unk44;
                if (other->unk40 + other->unk14 > (other->unk00 << 11) - (state->unk360 << 8))
                    other->unk14 = (other->unk00 << 11) - 0xF000 - other->unk40;
                if (other->unk44 + other->unk18 > (other->unk04 << 11) - 0xA000)
                    other->unk18 = (other->unk04 << 11) - 0xA000 - other->unk44;
            }
        }
    }
}

