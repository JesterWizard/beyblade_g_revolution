#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806f05c
/* match-compiler: old_agbcc */
// Centres the active camera on obj (clamped to the map), then moves every other
// camera that has a target by its own follow ratio (1/32 steps) of that shift.
void CameraCenterOnObject(struct Unk6EE48 *state, struct Unk68574 *obj)
{
    struct Unk68E54 *cam;
    s32 pos[3];
    s16 i;
    s32 y;

    cam = CameraGetActive(state);
    SceneObjGetPosition(obj, (u32 *)pos);
    state->unk354 |= 1;
    cam->unk14 = pos[0] - (cam->unk40 + ((0x78 - (obj->unk10 >> 1)) << 8));
    cam->unk18 = pos[1] - (cam->unk44 + (((y = (s16)obj->unkA2 + 0x50) - (obj->unk11 >> 1)) << 8));
    if (cam->unk40 + cam->unk14 < 0)
        cam->unk14 = -cam->unk40;
    if (cam->unk44 + cam->unk18 < 0)
        cam->unk18 = -cam->unk44;
    if (cam->unk40 + cam->unk14 > (cam->unk00 << 11) - 0xF000)
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
            }
        }
    }
}

