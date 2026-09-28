#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062790
/* match-compiler: old_agbcc */
// Proximity trigger: if obj's centre is within (rangeX, rangeY) pixels of a's
// centre, run obj's script (unkC4), or for a side-1 object whose profile
// passes sub_0802BC14, fire the one-shot event for slot. Returns 1 when in
// range; out of range re-arms the slot's flag.
s32 ProximityTriggerCheck(struct Unk68574 *a, struct Unk68574 *obj, u32 rangeX, u32 rangeY, s32 slot)
{
    s32 ax, ay, ox, oy;
    u32 dx, dy;
    s32 profile;

    ax = a->unk04 + ((a->unk10 >> 1) << 8);
    ay = a->unk08 + ((a->unk11 >> 1) << 8);
    ox = obj->unk04 + ((obj->unk10 >> 1) << 8);
    oy = obj->unk08 + ((obj->unk11 >> 1) << 8);
    dx = (ax - ox >= 0 ? ax - ox : ox - ax) >> 8;
    dy = (ay - oy >= 0 ? ay - oy : oy - ay) >> 8;
    if (dx <= rangeX && dy <= rangeY)
    {
        if (obj->unkD8 == (void *)1)
        {
            profile = BeybladeGetProfile((s32)obj->unkD4);
            if (sub_0802BC14(profile) == 0 || profile == -1)
            {
                if (obj->unkC4 != NULL)
                    sub_08059DC8((u32)obj, obj->unkC4);
            }
            else if (slot != -1 && gData_03000510[slot] == 0)
            {
                sub_080473E4();
                sub_08041F88();
                sub_0803FDD0(0xA72);
                gData_03000510[slot] = 1;
            }
        }
        else if (obj->unkC4 != NULL)
            sub_08059DC8((u32)obj, obj->unkC4);
        return 1;
    }
    if (slot != -1)
        gData_03000510[slot] = 0;
    return 0;
}

