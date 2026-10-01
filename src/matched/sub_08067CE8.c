#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067ce8
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* Loop-depth weighting raises px's allocation priority above `a` (retail: px=r4, a=r5). */
#define PX_WEIGHT(stmt) \
    do { do { do { do { do { do { do { do { do { stmt } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0); } while (0)

struct AnSprite
{
    u8 filler_00[8];
    s32 unk08;
    s32 unk0C;
    u32 unk10;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u8 filler_22[2];
    s32 unk24;
    u32 unk28;
    u32 unk2C;
    struct AnSprite *unk30;
};

void sub_08067CE8(struct Unk67BB8 *a, u32 b)
{
    s32 px;
    s32 py;
    struct Unk67BB8 *parent;
#define SPR ((struct AnSprite *)a->unkB8)
    struct AnSprite *spr;
    u32 pin;
    u32 m3;
    s32 out[3];

    if (a->unkB0 != 0)
    {
        ((void (*)(struct Unk67BB8 *, s32 *))a->unkB0)(a, out);
        px = out[0] >> 8;
        py = out[1] >> 8;
    }
    else
    {
        px = a->unk04 >> 8;
        py = a->unk08 >> 8;
    }
    parent = (struct Unk67BB8 *)a->unk3C;
    if (parent != NULL)
    {
        PX_WEIGHT(px -= (s32)parent->unk40 >> 8;);
        py -= (s32)parent->unk44 >> 8;
    }
    if (a->unk31 & 1)
        px -= (s16)a->unkA0 - (s8)a->unkA4;
    else
        px -= (s16)a->unkA0 + (s8)a->unkA4;
    py -= (s16)a->unkA2 + (s8)a->unkA5;
    if (a->unk70 == 0
        || px + ((a->unk10 * a->unk12) >> 8) < 0 || px > 0xEF
        || py + ((a->unk11 * a->unk14) >> 8) < 0 || py > 0x9F)
    {
        if (a->unkB8 != 0)
        {
            BtlObjPoolFree((void *)a->unkB8);
            a->unkB8 = 0;
        }
        return;
    }
    {
        if (a->unkB8 == 0)
        {
            a->unkB8 = (u32)BtlObjPoolAlloc(a->unkBC);
            if (a->unkB8 == 0)
                return;
            SPR->unk20 = 0;
            if (a->unk98 & 2)
                SPR->unk20 |= 1;
            SPR->unk1A = 0xFFFF;
            SPR->unk30 = NULL;
            SPR->unk24 = -1;
        }
        a->unk16 &= 0xFF;
        SPR->unk2C = (u32)a->unk00;
        SPR->unk1C = a->unk31;
        SPR->unk08 = px << 8;
        SPR->unk0C = py << 8;
        SPR->unk18 = a->unk22;
        SPR->unk16 = a->unk30;
        SPR->unk28 = (u32)a->unk00 + ((struct Unk6BB38 *)a->unk00)->unk10;
        spr = SPR;
        spr->unk10 = ((a->unk38 & 3) << 14) | ((~a->unk3A & 1) << 13) | (pin = ((a->unk39 & (m3 = 3)) << 10) | 0x1000) | ((a->unk38 & 0xC) << 28);
        {
            struct AnSprite *s2 = SPR;
            u32 pal = ((a->unk3A >> 1) & 0xF) << 12;
            u32 rot;

            if (a->unk3C != 0)
                rot = ((u8)sub_08069C14((struct Unk69C14 *)a->unk3C) + (s8)a->unk3B) & m3;
            else
                rot = (s8)a->unk3B & m3;
            s2->unk14 = (rot << 10) | pal;
        }
        SpriteApplyAffine((struct Unk70354 *)a->unkB8, a->unk12, a->unk14, a->unk16);
        spr = SPR;
        if (spr->unk30 != NULL)
            spr->unk10 = (spr->unk10 & 0xC1FFFFFF) | (pin = ((spr->unk30->unk08 & 0x3E0) << 20) | 0x100);
    }
}

