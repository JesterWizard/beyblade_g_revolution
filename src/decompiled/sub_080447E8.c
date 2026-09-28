#include "global.h"
#include "ram_map.h"

// Walks a -1-terminated id list and spawns a scene object for each kind-1
// entry of the 0x0807BE04 table, or parks the two position records of kind 2.
void sub_080447E8(void *arg)
{
    s32 *ids = arg;
    struct Unk6DEF4 *records;
    struct Unk6EE48 *state;
    s32 id;
    s32 *pos;
    struct Unk68574 *obj;
    struct Unk7BE04 *def;
    struct Unk59C98Src *part;

    records = (struct Unk6DEF4 *)sub_08062A14();
    state = (struct Unk6EE48 *)sub_0806EEC4((struct Unk6EE48 *)gData_03000198);
    while (*ids != -1)
    {
        id = *ids;
        if (sub_0803EDF0(id) == 1)
        {
            def = &gData_0807BE04[id];
            pos = (s32 *)sub_0806DEF4(records, def->unk02);
            if (pos != NULL)
            {
                obj = SceneObjSpawn((u32)state, (u32)gData_0807BE04[id].unk10, pos[0] >> 3, pos[1] >> 3);
                obj->unkD4 = (void *)id;
                obj->unkD8 = NULL;
                if (obj != NULL)
                {
                    obj->unk08 -= obj->unk11 << 8;
                    obj->unk04 -= (obj->unk10 >> 1) << 8;
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
                        sub_08059C98(part, (struct Unk59C98Owner *)obj, def, (void *)sub_0803EDC8(id));
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
            def = &gData_0807BE04[id];
            pos = (s32 *)sub_0806DEF4(records, def->unk02);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
            pos = (s32 *)sub_0806DEF4(records, def->unk02 + 1);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
        }
        ids++;
    }
}
