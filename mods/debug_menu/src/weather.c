#include "debug_menu.h"
#include "battle_types.h"

/* The weather entry: one of rain, snow, wind and heat, shown as falling
 * particles in the overworld and in battle, and played out in battle.
 *
 *   Rain  reduced grip: the blades slide further (drag is cut) and steer more
 *         weakly, so the player's top speed stays and the turns get wide.
 *   Snow  increased friction: drag goes up, everything slows down sooner.
 *   Wind  a sideways push on both blades that swings from one side of the
 *         screen to the other and gusts on the way.
 *   Heat  both blades lose spin faster: a share of what they have left, every
 *         few frames.
 *
 * The particles are plain OBJ sprites written into the last free OAM entries
 * (the same trick as thought_bubbles: the engine hides every entry it does not
 * use at the start of a frame, so a particle only lives while it is written
 * again each frame, and a weather switched off leaves nothing behind). Their
 * eight tiles go to the top of OBJ VRAM below the bubbles' and their colours to
 * one OBJ palette slot, written straight into palette RAM. */

#define SCREEN_W 240
#define SCREEN_H 160

#define OAM_FIRST 98 /* up to 125; thought_bubbles has 126 and 127 */
#define OAM_ENTRY(i) ((vu16 *)(0x07000000 + (i) * 8))
#define OAM_HIDE 0x0200 /* attribute 0: disabled */
#define OAM_WIDE 0x4000 /* attribute 0: 16x8 */
#define OAM_TALL 0x8000 /* attribute 0: 8x16 */
#define OAM_HFLIP 0x1000 /* attribute 1 */

#define FIRST_TILE 0x370 /* 9 tiles; the bubbles start at 0x380 */
#define OBJ_VRAM ((u32 *)(0x06010000 + FIRST_TILE * 32))
#define PAL_SLOT 14
#define PAL_RAM ((vu16 *)(0x05000200 + PAL_SLOT * 32))
#define TILE_WORDS (WEATHER_TILES * 8)

#define TILE_RAIN 0 /* and 1 */
#define TILE_FLAKE 2
#define TILE_DOT 3
#define TILE_STREAK 4 /* and 5 */
#define TILE_EMBER 6 /* and 7 */
#define TILE_SPARK 8

#define WEATHER_MAGIC 0x57EA7E12
#define PRIORITY_FIELD 1 /* behind the overworld's text layer */
#define PRIORITY_BATTLE 0 /* the arena's layers are all at 3 or 0 */

/* Positions are 1/16 pixel. */
#define PX(n) ((n) * 16)

/* Battle numbers. */
#define RAIN_DRAG 60 /* percent of the arena's drag left */
#define RAIN_STEER 60 /* percent of the d-pad's push left */
#define SNOW_DRAG 175
#define WIND_PEAK 10 /* push, 1/256 unit a frame squared; full steering is 32 */
#define WIND_CYCLE_SHIFT 3 /* wind clock ticks per step of the 256-step wave */
#define HEAT_PERIOD 40 /* frames between two losses */
#define HEAT_PERCENT 1 /* of the spin left, at least 1 */

extern void _08035984(struct BtlBody *body);

typedef char DebugStateFits[sizeof(struct DebugState) <= 0x600 ? 1 : -1];
typedef char WeatherStateFits[sizeof(struct WeatherState) <= 0x200 ? 1 : -1];

static u32 Kind(void)
{
    if (gDebug.magic != DBG_MAGIC)
        return WEATHER_OFF;
    return gDebug.value[DBG_WEATHER];
}

const char *WeatherName(u32 value)
{
    static const char *const names[WEATHER_COUNT] = { "OFF", "Rain", "Snow", "Wind", "Heat" };

    return value < WEATHER_COUNT ? names[value] : "?";
}

static s32 Sin(u32 angle)
{
    return gData_083C9544[angle & 0xFF];
}

static u32 Rand(void)
{
    gWeather.rng = gWeather.rng * 1664525 + 1013904223;
    return gWeather.rng >> 16;
}

static s32 Abs(s32 v)
{
    return v < 0 ? -v : v;
}

static u32 ParticleCount(u32 kind)
{
    switch (kind) {
    case WEATHER_RAIN:
        return 28;
    case WEATHER_SNOW:
        return 24;
    case WEATHER_WIND:
        return 16;
    case WEATHER_HEAT:
        return 20;
    }
    return 0;
}

/* ---- wind -------------------------------------------------------------- */

/* The wind on the screen, positive towards the right: a slow wave across the
 * screen with a faster ripple on it for gusts. */
static s32 WindAt(u32 clock)
{
    u32 a = (clock >> WIND_CYCLE_SHIFT) & 0xFF;
    s32 wave = (3 * Sin(a) + Sin(a * 5)) / 4; /* -256..256 */

    return wave * WIND_PEAK / 256;
}

/* The screen push as a push in the arena. The d-pad does the same turn
 * (sub_08030638 rotates by minus the camera's angle), so a wind towards the
 * right pushes the way a press of Right does. */
static void WindInArena(s32 *wx, s32 *wy)
{
    s32 camera = *(s32 *)((u8 *)gBattleWork + BTL_CAMERA_ANGLE);
    u32 rot = (u32)(-camera & 0xFFFF) >> 8;
    s32 s = gData_083C9544[rot];
    s32 c = gData_083C9544[rot + 0x40];

    *wx = (gWeather.wind * c) >> 8;
    *wy = -((gWeather.wind * s) >> 8);
}

/* ---- particles ---------------------------------------------------------- */

/* A particle that left the screen, or every one when the weather starts. */
static void Respawn(struct WeatherParticle *p, u32 kind, bool32 scatter)
{
    p->seed = Rand();
    p->phase = Rand();
    p->x = Rand() % PX(SCREEN_W);
    p->y = scatter ? Rand() % PX(SCREEN_H) : 0;
    switch (kind) {
    case WEATHER_RAIN:
        /* The drops lean to the left, so some start beyond the right edge. */
        p->x = Rand() % PX(SCREEN_W + 50);
        if (!scatter)
            p->y = -PX(16) - Rand() % PX(24);
        break;
    case WEATHER_SNOW:
        if (!scatter)
            p->y = -PX(8) - Rand() % PX(16);
        break;
    case WEATHER_WIND:
        p->y = Rand() % PX(SCREEN_H - 8);
        break;
    case WEATHER_HEAT:
        if (!scatter)
            p->y = PX(SCREEN_H) + Rand() % PX(16);
        break;
    }
}

static void Reset(u32 kind)
{
    u32 i;

    for (i = 0; i < WEATHER_MAX_PARTICLES; i++)
        Respawn(&gWeather.particle[i], kind, TRUE);
    gWeather.kind = kind;
}

static void StepParticles(u32 kind)
{
    u32 n = ParticleCount(kind);
    s32 wind = gWeather.wind;
    s32 speed = 48 + Abs(wind) * 18;
    u32 i;

    for (i = 0; i < n; i++) {
        struct WeatherParticle *p = &gWeather.particle[i];

        switch (kind) {
        case WEATHER_RAIN:
            p->y += 96 + (p->seed & 31);
            p->x -= 24 + (p->seed & 7);
            if (p->y > PX(SCREEN_H + 8) || p->x < -PX(8))
                Respawn(p, kind, FALSE);
            break;
        case WEATHER_SNOW:
            p->phase += 3 + (p->seed & 3);
            p->y += 12 + (p->seed & 7) * 2;
            p->x += Sin(p->phase) >> 5;
            if (p->y > PX(SCREEN_H + 8))
                Respawn(p, kind, FALSE);
            break;
        case WEATHER_WIND:
            /* They wrap round, so a change of direction needs no new spawn. */
            p->x += (wind < 0 ? -1 : 1) * (speed + (p->seed & 15) * 4);
            if (p->x > PX(SCREEN_W + 16)) {
                p->x -= PX(SCREEN_W + 32);
                p->y = Rand() % PX(SCREEN_H - 8);
            } else if (p->x < -PX(16)) {
                p->x += PX(SCREEN_W + 32);
                p->y = Rand() % PX(SCREEN_H - 8);
            }
            break;
        case WEATHER_HEAT:
            p->phase += 2 + (p->seed & 3);
            p->y -= 14 + (p->seed & 7) * 2;
            p->x += Sin(p->phase) >> 5;
            if (p->y < -PX(8))
                Respawn(p, kind, FALSE);
            break;
        }
    }
}

/* ---- drawing ----------------------------------------------------------- */

/* The tiles and colours stay where they were put. The engine can load other art
 * over them, so a few words are compared each frame and a mismatch loads again
 * (after VBlank: VRAM is not safe to write while the picture is drawn). */
static void LoadGfx(void)
{
    const u32 *src = &gWeatherTiles[0][0];
    u32 i;

    for (i = 0; i < TILE_WORDS; i += 7) {
        if (OBJ_VRAM[i] != src[i])
            break;
    }
    if (i < TILE_WORDS) {
        VBlankIntrWait();
        for (i = 0; i < TILE_WORDS; i++)
            OBJ_VRAM[i] = src[i];
    }
    for (i = 0; i < 16; i++) {
        if (PAL_RAM[i] != gWeatherPalette[i])
            PAL_RAM[i] = gWeatherPalette[i];
    }
}

static void Draw(u32 kind, u32 priority)
{
    u32 n = ParticleCount(kind);
    s32 wind = gWeather.wind;
    u32 i;

    LoadGfx();
    for (i = 0; i < n; i++) {
        struct WeatherParticle *p = &gWeather.particle[i];
        vu16 *oam = OAM_ENTRY(OAM_FIRST + i);
        s32 x = p->x >> 4;
        s32 y = p->y >> 4;
        u32 tile = TILE_RAIN;
        u32 shape = 0;
        u32 flip = 0;
        s32 width = 8;
        s32 height = 8;

        switch (kind) {
        case WEATHER_RAIN:
            shape = OAM_TALL;
            height = 16;
            break;
        case WEATHER_SNOW:
            tile = (p->seed & 1) ? TILE_FLAKE : TILE_DOT;
            break;
        case WEATHER_WIND:
            tile = TILE_STREAK;
            shape = OAM_WIDE;
            width = 16;
            if (wind < 0)
                flip = OAM_HFLIP;
            /* Calm spells show fewer streaks. */
            if ((p->seed & 15) >= Abs(wind) + 4)
                y = SCREEN_H;
            break;
        case WEATHER_HEAT:
            tile = (p->seed & 7) == 0 ? TILE_SPARK : TILE_EMBER + ((p->phase >> 4) & 1);
            break;
        }
        if (x <= -width || x >= SCREEN_W || y <= -height || y >= SCREEN_H) {
            oam[0] = OAM_HIDE;
            continue;
        }
        oam[0] = (y & 0xFF) | shape;
        oam[1] = (x & 0x1FF) | flip;
        oam[2] = (FIRST_TILE + tile) | (priority << 10) | (PAL_SLOT << 12);
    }
    gWeather.drawn = TRUE;
}

/* One frame of the weather, from either screen. */
static void Frame(u32 priority)
{
    u32 kind = Kind();

    if (gWeather.magic != WEATHER_MAGIC) {
        u8 *p = (u8 *)&gWeather;
        u32 i;

        for (i = 0; i < sizeof(gWeather); i++)
            p[i] = 0;
        gWeather.magic = WEATHER_MAGIC;
        gWeather.rng = 0x1234ABCD;
        gWeather.kind = WEATHER_OFF;
    }
    if (kind == WEATHER_OFF) {
        gWeather.drawn = FALSE;
        return;
    }
    if (gWeather.kind != kind)
        Reset(kind);
    gWeather.clock++;
    gWeather.wind = WindAt(gWeather.clock);
    StepParticles(kind);
    Draw(kind, priority);
}

/* Called from DebugFieldTick, once per overworld frame. */
void WeatherFieldTick(void)
{
    Frame(PRIORITY_FIELD);
}

/* Called from the battle frame, once per frame, by the player's input handler. */
void WeatherBattleTick(void)
{
    Frame(PRIORITY_BATTLE);
}

/* A battle starts: the heat has not touched anyone yet. */
void WeatherBattleStart(void)
{
    gWeather.heatTick[0] = 0;
    gWeather.heatTick[1] = 0;
}

/* ---- battle ------------------------------------------------------------ */

/* Replaces the bl to sub_08035984 (a body's motion step) in sub_080348E8, for
 * both blades. Drag and acceleration are changed for the step and put back. */
void WeatherMotion(struct BtlBody *body)
{
    u32 kind = Kind();
    s32 drag = body->drag;
    s32 ax = body->ax;
    s32 ay = body->ay;

    if (kind == WEATHER_RAIN && drag != 0) {
        body->drag = drag * RAIN_DRAG / 100;
        if (body->drag == 0)
            body->drag = 1;
    } else if (kind == WEATHER_SNOW) {
        body->drag = drag * SNOW_DRAG / 100;
    } else if (kind == WEATHER_WIND) {
        s32 wx;
        s32 wy;

        WindInArena(&wx, &wy);
        body->ax = ax + wx;
        body->ay = ay + wy;
    }
    _08035984(body);
    body->drag = drag;
    body->ax = ax;
    body->ay = ay;
}

/* The d-pad's push (TurbineSteer's speed): rain takes some of the grip away. */
s32 WeatherSteer(s32 speed)
{
    if (Kind() == WEATHER_RAIN)
        return speed * RAIN_STEER / 100;
    return speed;
}

/* Heat, once a frame per fighter (AbilityUpdate): a share of the spin goes. */
void WeatherDrain(struct BtlFighter *fighter)
{
    u8 *tick = &gWeather.heatTick[fighter->index == 0 ? 0 : 1];
    s32 rpm;
    s32 loss;

    if (Kind() != WEATHER_HEAT || fighter->stats == NULL)
        return;
    if (++*tick < HEAT_PERIOD)
        return;
    *tick = 0;
    rpm = fighter->stats->rpm;
    loss = rpm * HEAT_PERCENT / 100;
    if (loss < 1)
        loss = 1;
    fighter->stats->rpm = rpm > loss ? rpm - loss : 0;
}
