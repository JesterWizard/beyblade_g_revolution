#include "global.h"

// @ 0x0806ec20
/* match-compiler: old_agbcc */
// Bind a map header to a MapView: reset camera state, init each non-null BG
// layer (parallax origin when the layer's 8.8 offset is non-zero), set
// priorities, and load optional palettes / resources.
void sub_0806EC20(void *arg, u32 cfgArg, u32 dispArg, void *posArg)
{
    struct MapView *a = arg;
    struct MapFollowTable *cfg = (struct MapFollowTable *)cfgArg;
    struct MapOrigin *pos = posArg;
    u16 dispcnt = dispArg;
    s8 i;
    u8 bits = 0;
    u8 *flag_ptr;
    s32 mask;
    struct MapView *first;
    struct MapFollowEntry *l0;
    struct MapFollowEntry *layers;

    a->follow = cfg;
    a->target = (void *)(u32)bits;
    flag_ptr = &a->flags;
    mask = -2;
    *flag_ptr = mask & *flag_ptr;
    a->targetHandler = (void *)(u32)bits;
    a->unk348 = bits;
    a->unk355 = 0xF;
    a->unk356 = 0xFF;
    a->minX = bits;
    a->unk35E = bits;
    a->rightMargin = 0xF0;
    a->unk362 = 0xA0;
    a->unk364 = bits;
    a->unk368 = bits;
    *(vu16 *)0x04000050 = 0x3FFF;
    sub_08069894();
    first = a;
    l0 = cfg->entries;
    i = 0;
    layers = l0;
    for (; i <= 3; i++)
    {
        s32 px = pos[i].x;
        s32 py = pos[i].y;
        void *map = layers[i].active;

        if (map != NULL)
        {
            struct Unk68988 *bg = (struct Unk68988 *)&a->layers[i];

            bits |= 1 << i;
            if (bg != (struct Unk68988 *)first)
            {
                if (cfg->entries[i].unk04 != 0 || cfg->entries[i].unk08 != 0)
                {
                    BgMapInit(bg, i, map, 0x40, cfg->entries[i].unk0C | 1,
                        (l0->unk04 - cfg->entries[i].unk04) >> 8,
                        (l0->unk08 - cfg->entries[i].unk08) >> 8);
                    continue;
                }
            }
            BgMapInit((struct Unk68988 *)&a->layers[i], i, layers[i].active, 0x40,
                cfg->entries[i].unk0C | 1, px, py);
        }
    }
    BgSetPriorities(cfg->unk74_0, cfg->unk74_2, cfg->unk74_4, cfg->unk74_6);
    if (cfg->unk78 != NULL)
        BgPaletteLoad(cfg->unk78);
    if (cfg->unk7C != NULL)
        ObjPaletteLoad(cfg->unk7C);
    if (cfg->unk80 != NULL)
        ResourceBind(a->unk228, cfg->unk80);
    a->unk358 = ((s8)bits << 8) | dispcnt;
}
