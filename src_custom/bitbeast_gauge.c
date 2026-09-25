#include "global.h"

/*
 * Retail sub_08031094. Player 0 is BattleWork+0x478. The word at +0x2F0 is
 * ScaleRatio(current >> 8, max >> 8, 36): 0 is empty and 36 is full. The
 * summon path divides that word by 12. The bar object stores the inverse
 * (36 - fill); 36 is the empty frame used when the blade has no bit beast.
 */
struct BeastMark
{
    u8 filler[0x21];
    s8 mark;
};

struct BladeRef
{
    u8 filler[0x28];
    struct BeastMark *mark;
};

struct PlayerBattle
{
    u8 filler_00[4];
    struct BladeRef *blade;
    u8 filler_08[0x2E8]; /* bitBeastGauge at +0x2F0 */
    s32 bitBeastGauge;
};

#define PLAYER0_OFF 0x478
#define GAUGE_FULL 36

APPEND_TEXT void BitBeastGaugeFill__Replacement(struct PlayerBattle *player, s32 current, s32 maximum, struct Unk705DC *bar)
{
    s16 scaled;
    struct BladeRef *blade;
    struct BeastMark *mark;
    struct PlayerBattle *player0;

    player0 = NULL;
    if (gBattleWork != NULL)
        player0 = (struct PlayerBattle *)((u8 *)gBattleWork + PLAYER0_OFF);
    if (gRuntimeConfig.fullBitBeastGauge != FALSE && player == player0)
    {
        if (bar != NULL)
        {
            player->bitBeastGauge = GAUGE_FULL;
            bar->unk18 = 0;
        }
        return;
    }

    scaled = sub_08031124(current >> 8, maximum >> 8, GAUGE_FULL);
    if (bar == NULL)
        return;
    blade = player->blade;
    if (blade != NULL)
    {
        mark = blade->mark;
        if (mark != NULL && mark->mark <= 0)
        {
            player->bitBeastGauge = 0;
            bar->unk18 = GAUGE_FULL;
            return;
        }
    }
    if (scaled == -1)
        return;
    player->bitBeastGauge = scaled;
    bar->unk18 = (u16)(GAUGE_FULL - scaled);
}
