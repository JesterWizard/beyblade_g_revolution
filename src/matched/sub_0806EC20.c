#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806ec20
/* match-compiler: old_agbcc */
// Bind a map header to a MapView: reset camera state, init each non-null BG
// layer (offset from the base layer when its origin is non-zero), set BG
// priorities, and load optional palettes / resources. The high byte of unk358
// is the BG-enable mask, sign-extended from 8 bits.
void sub_0806EC20(void *view, void *table, u32 mode, void *origins)
{
    struct MapView *a = view;
    struct MapFollowTable *cfg = table;
    u16 dispcnt;
    struct MapOrigins *pos = origins;
    s8 i;
    s32 bits;
    s32 x;
    s32 y;
    struct MapLayer *baseLayer;
    struct MapFollowEntry *baseEntry;

    dispcnt = mode;
    bits = 0;
    a->follow = cfg;
    a->target = 0;
    a->skipFollow = 0;
    a->targetHandler = 0;
    a->unk348 = 0;
    a->unk355 = 0xF;
    a->unk356 = 0xFF;
    a->minX = 0;
    a->unk35E = 0;
    a->rightMargin = 0xF0;
    a->unk362 = 0xA0;
    a->unk364 = 0;
    a->unk368 = 0;
    REG_BLDCNT = 0x3FFF;
    sub_08069894();

    baseLayer = a->layers;
    baseEntry = cfg->entries;
    i = 0;
    do
    {
        x = pos->layer[i].x;
        y = pos->layer[i].y;
        if (cfg->entries[i].active != NULL)
        {
            bits = (u8)((1 << i) | bits);
            if (&a->layers[i] != baseLayer
                && (cfg->entries[i].unk04 != 0 || cfg->entries[i].unk08 != 0))
            {
                BgMapInit((struct Unk68988 *)&a->layers[i], i, cfg->entries[i].active, 0x40,
                    cfg->entries[i].unk0C | 1,
                    (baseEntry->unk04 - cfg->entries[i].unk04) >> 8,
                    (baseEntry->unk08 - cfg->entries[i].unk08) >> 8);
            }
            else
            {
                BgMapInit((struct Unk68988 *)&a->layers[i], i, cfg->entries[i].active, 0x40,
                    cfg->entries[i].unk0C | 1, x, y);
            }
        }
    } while (++i <= 3);
    BgSetPriorities(cfg->unk74_0, cfg->unk74_2, cfg->unk74_4, cfg->unk74_6);
    if (cfg->unk78 != NULL)
        BgPaletteLoad(cfg->unk78);
    if (cfg->unk7C != NULL)
        ObjPaletteLoad(cfg->unk7C);
    if (cfg->unk80 != NULL)
        ResourceBind(a->unk228, cfg->unk80);
    a->unk358 = ((bits << 24) >> 16) | dispcnt;
}

