#include "global.h"
#include "ram_map.h"
#include "finishers.h"

/* Retail rewards only one way of winning a clash: the spin it takes off. A blade
 * can also break (its wear reaches 100%, the match ends on the spot) and be rung
 * out (airborne above the wall), but a blade's wear only grows by half of what a
 * hit does beyond the target's endurance, so reaching 100% would take hundreds of
 * hits, and nothing in a clash ever throws a blade into the air. This mod gives
 * both of them a way in:
 *
 *   Break      every hit adds to the loser's wear, in proportion to the damage
 *              it did (a charged hit does three times a plain one, a blocked hit
 *              none). Wear is 100 * damage / maxRpm in percent, so the mod adds
 *              maxRpm * damage * BREAK_UNITS / 1000000 to it (at
 *              most BREAK_HIT_MAX for one hit).
 *   Ring-out   the loser is thrown away from the winner, faster the harder the
 *              hit was, and a charged attack that got most of its power through also pops it high enough to count
 *              as airborne for the wall (z >= 0x8000, see sub_08035C64). A blade
 *              that is thrown over the wall while it is that high is out. */

#define BREAK_UNITS 625 /* wear for each point of damage, in millionths of its starting spin (0.0625%) */
#define BREAK_HIT_MAX 31250 /* most wear (same unit) one hit may add: 3.125%, so a late-game blade still needs 32 hits */
#define BREAK_PLAYER 0 /* 1: the player's blade wears the same way (it is lost when it breaks) */

#define KNOCK_PLAYER 1 /* 0: only the opponent is thrown */
#define KNOCK_SPEED 45 /* velocity (1/256 unit per frame) for each point of damage */
#define KNOCK_MAX 3200 /* the step itself allows 4096 for one axis */
#define HOP_GREEN 4800 /* upward velocity from a medium (green) attack; about 4570 just reaches the wall's height of 0x8000, this stays above it for ~10 frames */
#define HOP_RED 5300 /* from a high (red) attack: a bit higher, ~17 frames above the wall's height */

extern s32 _080300D4(struct FinFighter *fighter);
extern void _08033630(s32 damage, s32 x, s32 y, u32 winner);

static void AddBreak(struct FinFighter *loser, s32 damage)
{
    s32 gain;

    if (loser->index == 0 && !BREAK_PLAYER)
        return;
    gain = damage * BREAK_UNITS;
    if (gain > BREAK_HIT_MAX)
        gain = BREAK_HIT_MAX;
    loser->damage += loser->maxRpm * gain / 1000000;
}

static void Throw(struct FinFighter *winner, struct FinFighter *loser, s32 damage)
{
    struct FinBody *from = winner->body;
    struct FinBody *to = loser->body;
    s32 dx;
    s32 dy;
    s32 dist;
    s32 speed;

    if (from == NULL || to == NULL || (loser->index == 0 && !KNOCK_PLAYER))
        return;
    /* In sixteenths of a unit: the squares stay within 32 bits. */
    dx = (to->x - from->x) >> 4;
    dy = (to->y - from->y) >> 4;
    if (dx == 0 && dy == 0) {
        /* On top of each other: away from the middle of the arena. */
        dx = (to->x - 0x10000) >> 4;
        dy = (to->y - 0x10000) >> 4;
    }
    dist = Sqrt(dx * dx + dy * dy);
    if (dist == 0)
        return;
    speed = damage * KNOCK_SPEED;
    if (speed > KNOCK_MAX)
        speed = KNOCK_MAX;
    to->vx = Div(dx * speed, dist);
    to->vy = Div(dy * speed, dist);
    /* Only a charged attack lifts, and only when most of its power got through:
     * a clash between two attackers halves both powers and a block takes the
     * rest off, which leaves the loser on the ground. */
    if (winner->action == FIN_ACTION_ATTACK && winner->charge >= 1 && damage * 2 > _080300D4(winner))
        to->vz = winner->charge >= 2 ? HOP_RED : HOP_GREEN;
}

/* Replaces the bl to sub_08033630 (the damage number of a clash that somebody
 * won) in sub_08032A88. */
void FinishersClash(s32 damage, s32 x, s32 y, u32 winner)
{
    struct FinFighter *player = (struct FinFighter *)((u8 *)gBattleWork + FIN_P_OFFSET);
    struct FinFighter *foe = (struct FinFighter *)((u8 *)gBattleWork + FIN_O_OFFSET);
    struct FinFighter *won = player->index == winner ? player : foe;
    struct FinFighter *lost = won == player ? foe : player;

    if (damage > 0 && player->stats != NULL && foe->stats != NULL) {
        AddBreak(lost, damage);
        Throw(won, lost, damage);
    }
    _08033630(damage, x, y, winner);
}
