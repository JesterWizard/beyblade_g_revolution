#include "debug_menu.h"
#include "battle_types.h"

/* The stadium entry: the arena's rules in battle. Every rule works on both
 * blades through the motion-step wrap (WeatherMotion calls StadiumMotion) and
 * the spin-loss wrap (StadiumDrain, from AbilityUpdate). Positions are in
 * units from the arena centre (the wall is at about 199).
 *
 *   Standard  nothing.
 *   Bowl      a pull to the centre that grows with the distance.
 *   Funnel    a pull three times as strong, steeper still near the wall.
 *   Corners   four pads on the diagonals that fire a blade across the arena.
 *   Ice       drag cut to a third and the d-pad's push to 40%.
 *   Sand      drag up by 40% and 2% of the spin gone every 20 frames.
 *   Magnetic  blades whose attack is at least their defence are one pole, the
 *             others the other: like poles push each other apart, unlike pull.
 *   Volcano   every 15 seconds the centre erupts: 1.5 s of warning (embers on
 *             the screen), then 2 s in which blades near the centre are thrown
 *             outwards and burn.
 *   Ultimate  all of it at once. */

#define BOWL_SHIFT 12 /* acceleration = offset (1/256 unit) >> this */
#define FUNNEL_SHIFT 10
#define PAD_DIAG 100 /* pads at (+-100, +-100) */
#define PAD_RADIUS 22
#define PAD_KICK 1800 /* velocity given, 1/256 unit a frame */
#define PAD_COOLDOWN 60
#define ICE_DRAG 30 /* percent */
#define ICE_STEER 40
#define SAND_DRAG 140
#define SAND_PERIOD 20
#define SAND_PERCENT 2
#define MAGNET_RANGE 150
#define MAGNET_FORCE 12 /* at touching distance */
#define VOLCANO_PERIOD 900
#define VOLCANO_WARN_AT 600
#define VOLCANO_ERUPT_AT 690
#define VOLCANO_END_AT 810
#define LAVA_RADIUS 70
#define LAVA_PUSH 40
#define LAVA_PERIOD 10
#define LAVA_PERCENT 3

const char *StadiumName(u32 value)
{
    static const char *const names[STADIUM_COUNT] = {
        "Standard", "Bowl", "Funnel", "Four Corners", "Ice", "Sand", "Magnetic", "Volcano", "Ultimate"
    };

    return value < STADIUM_COUNT ? names[value] : "?";
}

static u32 Kind(void)
{
    if (gDebug.magic != DBG_MAGIC)
        return STADIUM_STANDARD;
    return gDebug.value[DBG_STADIUM];
}

/* Whether a rule is in force: its own stadium, or the Ultimate one. */
bool32 StadiumUses(u32 stadium)
{
    u32 kind = Kind();

    return kind == stadium || kind == STADIUM_ULTIMATE;
}

static s32 Abs(s32 v)
{
    return v < 0 ? -v : v;
}

void StadiumStart(void)
{
    gWeather.stadiumClock = 0;
    gWeather.padCool[0] = gWeather.padCool[1] = 0;
    gWeather.sandTick[0] = gWeather.sandTick[1] = 0;
}

/* Once a frame (WeatherBattleTick). */
void StadiumTick(void)
{
    u32 i;

    if (Kind() == STADIUM_STANDARD)
        return;
    gWeather.stadiumClock++;
    if (gWeather.stadiumClock >= VOLCANO_PERIOD)
        gWeather.stadiumClock = 0;
    for (i = 0; i < 2; i++) {
        if (gWeather.padCool[i] != 0)
            gWeather.padCool[i]--;
    }
}

u32 StadiumEruption(void)
{
    u32 t = gWeather.stadiumClock;

    if (!StadiumUses(STADIUM_VOLCANO))
        return ERUPT_CALM;
    if (t >= VOLCANO_ERUPT_AT && t < VOLCANO_END_AT)
        return ERUPT_ACTIVE;
    if (t >= VOLCANO_WARN_AT && t < VOLCANO_ERUPT_AT)
        return ERUPT_WARN;
    return ERUPT_CALM;
}

/* The d-pad's push (TurbineSteer's speed). */
s32 StadiumSteer(s32 speed)
{
    if (StadiumUses(STADIUM_ICE))
        return speed * (Kind() == STADIUM_ULTIMATE ? 70 : ICE_STEER) / 100;
    return speed;
}

static struct BtlFighter *FighterOf(u32 index)
{
    return (struct BtlFighter *)((u8 *)gBattleWork + (index == 0 ? 0x478 : 0x790));
}

static s32 Polarity(const struct BtlFighter *f)
{
    if (f->stats == NULL)
        return 1;
    return f->stats->attack >= f->stats->defense ? 1 : -1;
}

/* What the stadium does to a body's next motion step: a drag factor, an
 * acceleration, and (pads) a kick straight into the velocity. */
void StadiumMotion(struct BtlBody *body, s32 *dragPercent, s32 *ax, s32 *ay)
{
    u32 mine = body == (struct BtlBody *)((u8 *)gBattleWork + 0x328) ? 0 : 1;
    s32 dx = body->x - BTL_ARENA_CENTER;
    s32 dy = body->y - BTL_ARENA_CENTER;
    u32 kind = Kind();

    if (kind == STADIUM_STANDARD)
        return;

    if (StadiumUses(STADIUM_BOWL)) {
        *ax -= dx >> BOWL_SHIFT;
        *ay -= dy >> BOWL_SHIFT;
    }
    if (StadiumUses(STADIUM_FUNNEL)) {
        s32 shift = kind == STADIUM_ULTIMATE ? FUNNEL_SHIFT + 1 : FUNNEL_SHIFT;

        *ax -= dx >> shift;
        *ay -= dy >> shift;
    }
    if (StadiumUses(STADIUM_ICE))
        *dragPercent = *dragPercent * ICE_DRAG / 100;
    if (StadiumUses(STADIUM_SAND))
        *dragPercent = *dragPercent * SAND_DRAG / 100;

    if (StadiumUses(STADIUM_CORNERS) && gWeather.padCool[mine] == 0) {
        s32 ux = dx >> 8;
        s32 uy = dy >> 8;
        s32 px = ux < 0 ? -PAD_DIAG : PAD_DIAG;
        s32 py = uy < 0 ? -PAD_DIAG : PAD_DIAG;

        if (Abs(ux - px) < PAD_RADIUS && Abs(uy - py) < PAD_RADIUS
            && (ux - px) * (ux - px) + (uy - py) * (uy - py) < PAD_RADIUS * PAD_RADIUS) {
            s32 n = Sqrt(ux * ux + uy * uy);

            if (n > 0) {
                /* Across the centre to the far pad. */
                body->vx = -ux * PAD_KICK / n;
                body->vy = -uy * PAD_KICK / n;
                gWeather.padCool[mine] = PAD_COOLDOWN;
            }
        }
    }

    if (StadiumUses(STADIUM_MAGNETIC)) {
        struct BtlFighter *me = FighterOf(mine);
        struct BtlFighter *other = FighterOf(1 - mine);

        if (other->body != NULL) {
            s32 ox = (other->body->x - body->x) >> 8;
            s32 oy = (other->body->y - body->y) >> 8;
            s32 dist = Sqrt(ox * ox + oy * oy);

            if (dist > 0 && dist < MAGNET_RANGE) {
                s32 force = MAGNET_FORCE * (MAGNET_RANGE - dist) / MAGNET_RANGE;

                if (Polarity(me) == Polarity(other))
                    force = -force;
                *ax += ox * force / dist;
                *ay += oy * force / dist;
            }
        }
    }

    if (StadiumEruption() == ERUPT_ACTIVE) {
        s32 ux = dx >> 8;
        s32 uy = dy >> 8;
        s32 dist = Sqrt(ux * ux + uy * uy);

        if (dist < LAVA_RADIUS) {
            if (dist == 0) {
                ux = 1;
                dist = 1;
            }
            *ax += ux * LAVA_PUSH / dist;
            *ay += uy * LAVA_PUSH / dist;
        }
    }
}

/* Spin lost to the sand and the lava, once a frame per fighter. */
void StadiumDrain(struct BtlFighter *fighter)
{
    u8 *tick = &gWeather.sandTick[fighter->index == 0 ? 0 : 1];
    bool32 sand = StadiumUses(STADIUM_SAND);
    bool32 lava = StadiumEruption() == ERUPT_ACTIVE;
    s32 percent;
    s32 period;
    s32 rpm;
    s32 loss;

    if (fighter->stats == NULL || fighter->body == NULL || (!sand && !lava))
        return;
    if (lava) {
        s32 ux = (fighter->body->x - BTL_ARENA_CENTER) >> 8;
        s32 uy = (fighter->body->y - BTL_ARENA_CENTER) >> 8;

        lava = ux * ux + uy * uy < LAVA_RADIUS * LAVA_RADIUS;
    }
    if (!sand && !lava)
        return;
    period = lava ? LAVA_PERIOD : SAND_PERIOD;
    percent = lava ? LAVA_PERCENT : SAND_PERCENT;
    if (++*tick < period)
        return;
    *tick = 0;
    rpm = fighter->stats->rpm;
    loss = rpm * percent / 100;
    if (loss < 1)
        loss = 1;
    fighter->stats->rpm = rpm > loss ? rpm - loss : 0;
}
