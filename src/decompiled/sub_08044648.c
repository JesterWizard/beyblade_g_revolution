#include "global.h"
#include "ram_map.h"

// Walks a -1-terminated list of Beyblade ids and spawns a scene object for
// each roster entry (side 1), or parks its position record (side 2).
void BeybladeSpawnList(void *arg)
{
    s32 *ids;
    struct Unk6DEF4 *records;
    struct Unk6EE48 *state;
    s32 id;
    u16 side;
    s32 *pos;
    struct Unk68574 *obj;
    struct BeybladeDef *def;

    ids = arg;
    records = (struct Unk6DEF4 *)sub_08062A14();
    state = (struct Unk6EE48 *)sub_0806EEC4((struct Unk6EE48 *)gData_03000198);
    while (*ids != -1)
    {
        id = *ids;
        side = GetIndexedRecordWord((s16)*ids);
        if (side == 1)
        {
            def = &gData_08075AB8[id];
            pos = (s32 *)sub_0806DEF4(records, def->variant);
            if (pos != NULL)
            {
                obj = SceneObjSpawn((u32)state, gData_08075AB8[id].param, pos[0] >> 3, pos[1] >> 3);
                obj->unkD4 = (void *)id;
                obj->unkD8 = (void *)(u32)side;
                if (gData_08075AB8[id].type > -1)
                    obj->unk3B = gData_08075AB8[id].type;
                if (obj != NULL)
                {
                    obj->unk08 -= obj->unk11 << 8;
                    obj->unk04 -= (obj->unk10 >> 1) << 8;
                    if ((s16)def->flags != -1)
                        BtlEntitySelectByKeyDefault((struct Unk680CC *)obj, def->flags);
                    if (gData_08075AB8[id].script != 0)
                    {
                        obj->unkC4 = (void *)gData_08075AB8[id].script;
                        sub_080626B8((struct Unk626B8 *)&gData_03000198->unk0524, (u32)obj);
                        obj->unkCC = 8;
                        obj->unkD0 = 8;
                    }
                    if (gData_08075AB8[id].part != 0)
                        ((void (*)(u32, struct Unk68574 *))sub_08059C98)(gData_08075AB8[id].part, obj);
                    else
                        obj->unkC8 = (void *)gData_08075AB8[id].part;
                }
            }
        }
        else if (GetIndexedRecordWord((s16)*ids) == 2)
        {
            pos = (s32 *)sub_0806DEF4(records, gData_08075AB8[id].variant);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
        }
        ids++;
    }
}
