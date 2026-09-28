#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08043c70
/* match-compiler: old_agbcc */
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Loads map `map`: copies its header to gData_03000560, decompresses each
// compressed layer into a heap buffer, then places `obj` either at the saved
// position (`restore`) or at spawn point `spawn`, and sets the camera.
void sub_08043C70(struct Unk68574 *obj, const struct Unk0560 *map, u32 modeArg, u32 spawnArg, u32 restore)
{
    u16 mode = modeArg;
    u16 spawn = spawnArg;
    struct Unk0560 *cur;
    struct Unk0560Layer *layer;
    struct Unk0560Handle **slot;
    struct Unk0560LayerSrc *src;
    struct Unk0560Handle *buf;
    s32 i;
    u32 size;
    s32 x;
    s32 y;

    ((CpuCopyFunc)gData_080BB8C0[0])(map, &gData_03000560, sizeof(struct Unk0560));
    sub_08043C28();
    cur = &gData_03000560;
    layer = cur->layers;
    slot = gData_030005F0;
    for (i = 0; i < 4; i++)
    {
        src = layer->unk00;
        if (src != NULL)
        {
            size = src->unk00 >> 8;
            if (src->unk04 != 0x20)
            {
                buf = HeapAlloc(size);
                if (buf == NULL)
                {
                    layer->unk00 = NULL;
                    *slot = NULL;
                }
                else
                {
                    *slot = buf;
                    VBlankIntrWait();
                    LZ77UnCompWram(src, buf->unk00);
                    layer->unk00 = buf->unk00;
                }
            }
        }
        layer++;
        slot++;
    }
    VBlankIntrWait();
    sub_08062988(gData_03000560.unk80);
    if (restore)
    {
        obj->unk04 = gMainWorkPtr->unk0868;
        obj->unk08 = gMainWorkPtr->unk086C;
        x = ((s32)gMainWorkPtr->unk0868 >> 8) - 0x78;
        y = ((s32)gMainWorkPtr->unk086C >> 8) - 0x50;
    }
    else
    {
        s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), spawn);

        obj->unk04 = (pos[0] << 5) - ((obj->unk10 >> 1) << 8);
        obj->unk08 = (pos[1] << 5) - ((obj->unk11 >> 1) << 8);
        x = (pos[0] >> 3) - 0x78;
        y = (pos[1] >> 3) - 0x50;
    }
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    VBlankIntrWait();
    sub_0806EBF8(gMainWorkPtr, (u32)&gData_03000560, mode, x, y);
}
