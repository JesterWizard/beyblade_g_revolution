#include "debug_menu.h"
#include "battle_types.h"

/* The special abilities of the menu's last section. Each one wraps a bl in the
 * battle code (hooks.txt) and works on the human player only (fighter index
 * 0); the opponent plays by the retail rules.
 *
 *   Siphon      10% of the spin a clash takes from the opponent is added to
 *               the player's.
 *   Gunner      the bit beast gauge fills half as fast again.
 *   Steel Wall  half of what attacking and dodging cost in spin is given back.
 *   Turbine     travelling the stadium edge builds a charge that speeds the
 *               player's steering up and makes attacks hit harder; it is lost
 *               when the blades collide.
 *   Rocket      the recovery wait after an attack counts down twice as fast.
 */

#define SIPHON_SHARE 10 /* percent of the damage dealt */
#define MAX_RPM 32767 /* the signed spin step breaks above this */

/* Turbine. The charge counts frames: it grows by one for every frame the
 * player travels along the edge and is lost on a collision. At full charge
 * steering is TURBINE_SPEED percent stronger (the body's speed settles at a
 * level proportional to it) and an attack hits TURBINE_ATTACK percent harder. */
#define TURBINE_FULL 300 /* 5 seconds */
#define TURBINE_SPEED 100
#define TURBINE_ATTACK 50
#define TURBINE_EDGE 140 /* units from the centre; the wall is at about 199 */
#define TURBINE_TRAVEL 256 /* tangential speed, 1/256 units per frame, that counts as travelling */

extern void _08034BE0(struct BtlFighter *fighter, struct BtlFighter *other);
extern struct BtlFighter *_0802FFAC(struct BtlFighter *a, struct BtlFighter *b, s32 *kind, s32 *damage);
extern s32 _080300D4(struct BtlFighter *fighter);
extern void _08032A88(struct BtlFighter *a, struct BtlFighter *b);
extern void _08030638(struct BtlFighter *fighter, s32 speed);
extern void _080348E8(struct BtlFighter *fighter, struct BtlFighter *other);

static bool32 Active(u32 item)
{
    return gDebug.magic == DBG_MAGIC && gDebug.value[item];
}

static bool32 IsPlayer(const struct BtlFighter *fighter)
{
    return fighter->index == 0;
}

static void AddRpm(struct BtlFighter *fighter, s32 amount)
{
    s32 rpm = fighter->stats->rpm + amount;

    fighter->stats->rpm = rpm > MAX_RPM ? MAX_RPM : rpm;
}

/* A battle starts: nothing carried over from the last one. */
void AbilitiesBattleStart(void)
{
    gDebug.turbine = 0;
    gDebug.siphonRest = 0;
}

/* ---- Turbine ----------------------------------------------------------- */

/* Counted once a frame for the player: on the edge and moving across the line
 * from the centre (not towards or away from it) builds the charge. */
static void TurbineTick(struct BtlFighter *player)
{
    struct BtlBody *body = player->body;
    s32 dx;
    s32 dy;
    s32 dist;
    s32 across;

    if (!Active(DBG_TURBINE) || ((u8 *)gBattleWork)[BTL_COLLISION]) {
        gDebug.turbine = 0;
        return;
    }
    if (body == NULL)
        return;
    dx = (BTL_ARENA_CENTER - body->x) >> 8;
    dy = (BTL_ARENA_CENTER - body->y) >> 8;
    dist = Sqrt(dx * dx + dy * dy);
    if (dist < TURBINE_EDGE)
        return;
    across = dx * body->vy - dy * body->vx;
    if (across < 0)
        across = -across;
    if (across < TURBINE_TRAVEL * dist)
        return;
    if (gDebug.turbine < TURBINE_FULL)
        gDebug.turbine++;
}

/* Replaces both bls to sub_08030638 (steer by the d-pad) in sub_08034BE0. */
void TurbineSteer(struct BtlFighter *fighter, s32 speed)
{
    if (Active(DBG_TURBINE) && IsPlayer(fighter))
        speed = speed * (100 * TURBINE_FULL + gDebug.turbine * TURBINE_SPEED) / (100 * TURBINE_FULL);
    _08030638(fighter, speed);
}

/* Replaces both bls to sub_080300D4 (the power of a fighter's action) in the
 * clash resolver sub_0802FFAC. */
s32 TurbinePower(struct BtlFighter *fighter)
{
    s32 power = _080300D4(fighter);

    if (Active(DBG_TURBINE) && IsPlayer(fighter) && fighter->action == BTL_ACTION_ATTACK)
        power = power * (100 * TURBINE_FULL + gDebug.turbine * TURBINE_ATTACK) / (100 * TURBINE_FULL);
    return power;
}

/* ---- the wraps --------------------------------------------------------- */

/* Replaces both bls to sub_08034BE0 (a fighter's input handler) in the battle
 * frame. Attacking and dodging take their spin cost inside it. */
void AbilityHandler(struct BtlFighter *fighter, struct BtlFighter *other)
{
    s32 before;
    s32 lost;

    if (fighter->stats == NULL || !IsPlayer(fighter)) {
        _08034BE0(fighter, other);
        return;
    }
    TurbineTick(fighter);
    before = fighter->stats->rpm;
    _08034BE0(fighter, other);
    lost = before - fighter->stats->rpm;
    if (Active(DBG_STEEL_WALL) && lost > 0)
        fighter->stats->rpm += (lost + 1) / 2; /* odd costs round in the player's favour */
}

/* Replaces the bl to sub_0802FFAC (resolve a clash) in sub_08032A88. */
struct BtlFighter *AbilityClash(struct BtlFighter *a, struct BtlFighter *b, s32 *kind, s32 *damage)
{
    struct BtlFighter *player = IsPlayer(a) ? a : b;
    struct BtlFighter *foe = player == a ? b : a;
    struct BtlFighter *winner;
    s32 foeRpm;
    s32 dealt;

    if (a->stats == NULL || b->stats == NULL || !IsPlayer(player))
        return _0802FFAC(a, b, kind, damage);
    foeRpm = foe->stats->rpm;
    winner = _0802FFAC(a, b, kind, damage);
    dealt = foeRpm - foe->stats->rpm;
    if (Active(DBG_SIPHON) && dealt > 0) {
        /* A hit is only a few spin points, so the hundredths are carried over. */
        gDebug.siphonRest += dealt * SIPHON_SHARE;
        AddRpm(player, gDebug.siphonRest / 100);
        gDebug.siphonRest %= 100;
    }
    gDebug.turbine = 0;
    return winner;
}

/* Replaces the bl to sub_08032A88 (blades in contact; fills the gauge) in the
 * battle frame. */
void AbilityContact(struct BtlFighter *a, struct BtlFighter *b)
{
    u8 *battle = (u8 *)gBattleWork;
    s32 *gauge = (s32 *)(battle + BTL_GAUGE);
    s32 before = *gauge;
    s32 now;

    _08032A88(a, b);
    now = *gauge;
    if (Active(DBG_GUNNER) && now > before) {
        now += (now - before) / 2;
        if (now > *(s32 *)(battle + BTL_GAUGE_CAP))
            now = *(s32 *)(battle + BTL_GAUGE_CAP);
        *gauge = now;
    }
}

/* Replaces both bls to sub_080348E8 (a fighter's frame update) in the battle
 * step. Its timed state counts the recovery after an action down by one a
 * frame; Rocket takes a second one off. */
void AbilityUpdate(struct BtlFighter *fighter, struct BtlFighter *other)
{
    s32 before = fighter->timer;

    _080348E8(fighter, other);
    if (Active(DBG_ROCKET) && IsPlayer(fighter) && before > 0 && fighter->timer == before - 1)
        fighter->timer = before - 2;
}
