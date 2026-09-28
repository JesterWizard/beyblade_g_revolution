#include "global.h"
#include "ram_map.h"
#include "battle.h"

struct EcLayer
{
    void *unk00;
    s32 unk04;
    s32 unk08;
    u32 unk0C;
    u8 filler_10[8];
};

struct EcCfg
{
    u8 filler_00[0x14];
    struct EcLayer layer[4];
    u8 unk74;
    u8 filler_75[3];
    void *unk78;
    void *unk7C;
    void *unk80;
};

struct EcPos
{
    s32 x;
    s32 y;
};

struct EcState
{
    u8 bg[4][0x88];
    u8 filler_220[0];
    struct EcCfg *unk220;
    s32 unk224;
    u8 unk228[0x11C];
    s32 unk344;
    s32 unk348;
    u8 filler_34C[8];
    u8 unk354;
    u8 unk355;
    u8 unk356;
    u8 filler_357;
    u16 unk358;
    u8 filler_35A[2];
    s16 unk35C;
    u16 unk35E;
    u16 unk360;
    u16 unk362;
    s32 unk364;
    s32 unk368;
};

void BgMapInit(struct Unk68988 *state, u8 index, void *arg2, u16 limit, u16 mode, s32 x, s32 y);

void sub_0806EC20(void *arg, u32 cfgArg, u32 dispArg, void *posArg)
{
    struct EcState *a = arg;
    struct EcCfg *cfg = (struct EcCfg *)cfgArg;
    struct EcPos *pos = posArg;
    u16 dispcnt = dispArg;
    s8 i;
    u8 bits = 0;
    struct EcState *first = a;
    struct EcLayer *l0 = cfg->layer;
    struct EcLayer *layers = cfg->layer;

    a->unk220 = cfg;
    a->unk224 = bits;
    a->unk354 &= ~1;
    a->unk344 = bits;
    a->unk348 = bits;
    a->unk355 = 0xF;
    a->unk356 = 0xFF;
    a->unk35C = bits;
    a->unk35E = bits;
    a->unk360 = 0xF0;
    a->unk362 = 0xA0;
    a->unk364 = bits;
    a->unk368 = bits;
    *(vu16 *)0x04000050 = 0x3FFF;
    sub_08069894();
    for (i = 0; i <= 3; i++)
    {
        s32 px = pos[i].x;
        s32 py = pos[i].y;
        void *map = layers[i].unk00;

        if (map != NULL)
        {
            struct Unk68988 *bg = (struct Unk68988 *)a->bg[i];

            bits |= 1 << i;
            if (bg != (struct Unk68988 *)first)
            {
                s32 dx = l0->unk04;
                s32 dy = l0->unk08;
                if (cfg->layer[i].unk04 != 0 || cfg->layer[i].unk08 != 0)
                    BgMapInit(bg, i, map, 0x40, cfg->layer[i].unk0C | 1, (dx - cfg->layer[i].unk04) >> 8, (dy - cfg->layer[i].unk08) >> 8);
            }
            else
            {
                BgMapInit(bg, i, map, 0x40, cfg->layer[i].unk0C | 1, px, py);
            }
        }
    }
    sub_08069B78(cfg->unk74 & 3, (cfg->unk74 >> 2) & 3, (cfg->unk74 >> 4) & 3, cfg->unk74 >> 6);
    if (cfg->unk78 != NULL)
        sub_080679A4(cfg->unk78);
    if (cfg->unk7C != NULL)
        sub_080679C0(cfg->unk7C);
    if (cfg->unk80 != NULL)
        sub_0806BC0C(a->unk228, cfg->unk80);
    a->unk358 = (bits << 8) | dispcnt;
}
