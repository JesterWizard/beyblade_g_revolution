#include "debug_menu.h"

/* The menu's state is kept in the save, in the 8-byte EEPROM blocks that
 * follow the save slot. Slot 0 uses blocks 0..2 (header) and 3..0x3EE (data);
 * the 8 KB chip has 1024 blocks, so 0x3EF..0x3FF are free. The menu may use up
 * to DBG_SAVE_BYTES of them (13 blocks); the last 4 stay unused.
 *
 * They are outside the slot image, so retail's checksum does not cover them:
 * the record carries its own tag and sum, and a record that does not check out
 * (an old save, a blank chip) loads as "every entry off".
 *
 * Saved: every entry's value, the originals the value entries put back when
 * switched off, and what the collection entries added, so switching an entry
 * off after a reload still takes back exactly what it gave. Not saved: the
 * original bit beast EXP of each blader (110 bytes), so Max BitBeast EXP does
 * not restore after a reload. */
#define DBG_SAVE_BLOCK 0x3EF
#define DBG_SAVE_BYTES 100
#define SAVE_TAG 0xDB
#define SAVE_SEED 0x5A5A
#define RETRIES 8

#define HAS_STRENGTH 0x01
#define HAS_EXP 0x02
#define HAS_CREDITS 0x04
#define ON_CHARACTERS 0x08
#define ON_BLADES 0x10
#define ON_PARTS 0x20
#define ON_LOCATIONS 0x40

struct SavedDebug {
    u32 credits;
    s16 exp;
    u16 sum; /* SAVE_SEED + every byte after this field */
    u8 tag;
    u8 value[DBG_SAVED_ITEMS];
    u8 has; /* HAS_* and ON_* */
    s8 strength;
    u8 ripcords; /* GROUP_RIPCORD / LAUNCHER / BITCHIP ids this cheat added, one bit per id */
    u8 launchers;
    u8 bitChips;
    u8 nodeAdded[MAP_NODES];
    u8 blades[(BEYBLADE_IDS + 7) / 8];
    u8 rowFlags[(BLADER_ROWS + 7) / 8]; /* bit i: blader row i was already collected */
};

/* The abilities were added after the record above had shipped. Their on/off
 * bits sit right behind it, in the bytes its last block already carried, with a
 * tag and sum of their own: a record from before them has other bytes there,
 * fails the check and loads with the abilities off, everything else intact. */
struct SavedAbilities {
    u8 tag;
    u8 on; /* bit i: DBG_ABILITY_FIRST + i is on */
    u16 sum;
};

#define ABILITY_TAG 0xAB

/* The weather came later still: its value sits behind the abilities' bits, with
 * a tag and sum of its own, so a record without it loads with the weather off. */
struct SavedWeather {
    u8 tag;
    u8 value;
    u16 sum;
};

#define WEATHER_TAG 0xBE

/* And the stadium, the same way. */
struct SavedStadium {
    u8 tag;
    u8 value;
    u16 sum;
};

#define STADIUM_TAG 0x5D

#define SAVE_USED (sizeof(struct SavedDebug) + sizeof(struct SavedAbilities) + sizeof(struct SavedWeather) + sizeof(struct SavedStadium))
#define SAVE_BLOCKS ((SAVE_USED + 7) / 8)

typedef char SavedDebugFits[SAVE_USED <= DBG_SAVE_BYTES ? 1 : -1];
typedef char AbilityBitsFit[DBG_ABILITY_COUNT <= 8 ? 1 : -1];

extern u32 sub_080677A8(u32 address, void *data);
extern u16 sub_08067634(u32 address, u32 data);
extern s32 sub_08067584(u32 address, void *out);
extern s32 sub_08044F14(u32 slot, void *image);

static u16 Sum(const struct SavedDebug *s)
{
    const u8 *p = (const u8 *)&s->tag;
    u32 sum = SAVE_SEED;
    u32 i;

    for (i = 0; i < sizeof(*s) - ((u32)p - (u32)s); i++)
        sum += p[i];
    return sum;
}

static struct SavedAbilities *Abilities(const struct SavedDebug *s)
{
    return (struct SavedAbilities *)((u8 *)s + sizeof(*s));
}

static u16 AbilitySum(const struct SavedAbilities *a)
{
    return SAVE_SEED + a->tag + a->on;
}

static struct SavedWeather *Weather(const struct SavedDebug *s)
{
    return (struct SavedWeather *)((u8 *)s + sizeof(*s) + sizeof(struct SavedAbilities));
}

static struct SavedStadium *Stadium(const struct SavedDebug *s)
{
    return (struct SavedStadium *)((u8 *)s + sizeof(*s) + sizeof(struct SavedAbilities) + sizeof(struct SavedWeather));
}

static u16 StadiumSum(const struct SavedStadium *w)
{
    return SAVE_SEED + w->tag + w->value;
}

static u16 WeatherSum(const struct SavedWeather *w)
{
    return SAVE_SEED + w->tag + w->value;
}

static void Pack(struct SavedDebug *s)
{
    struct SavedAbilities *a = Abilities(s);
    u32 i;
    u8 *p = (u8 *)s;

    for (i = 0; i < sizeof(*s); i++)
        p[i] = 0;
    s->tag = SAVE_TAG;
    for (i = 0; i < DBG_SAVED_ITEMS; i++)
        s->value[i] = gDebug.value[i];
    a->tag = ABILITY_TAG;
    a->on = 0;
    for (i = 0; i < DBG_ABILITY_COUNT; i++) {
        if (gDebug.value[DBG_ABILITY_FIRST + i])
            a->on |= 1 << i;
    }
    a->sum = AbilitySum(a);
    Weather(s)->tag = WEATHER_TAG;
    Weather(s)->value = gDebug.value[DBG_WEATHER];
    Weather(s)->sum = WeatherSum(Weather(s));
    Stadium(s)->tag = STADIUM_TAG;
    Stadium(s)->value = gDebug.value[DBG_STADIUM];
    Stadium(s)->sum = StadiumSum(Stadium(s));
    s->has = (gDebug.hasStrength ? HAS_STRENGTH : 0) | (gDebug.hasExp ? HAS_EXP : 0)
        | (gDebug.hasCredits ? HAS_CREDITS : 0) | (gDebug.charactersOn ? ON_CHARACTERS : 0)
        | (gDebug.bladesOn ? ON_BLADES : 0) | (gDebug.partsOn ? ON_PARTS : 0)
        | (gDebug.locationsOn ? ON_LOCATIONS : 0);
    s->strength = gDebug.strength;
    s->exp = gDebug.exp;
    s->credits = gDebug.credits;
    s->ripcords = gDebug.parts[GROUP_RIPCORD];
    s->launchers = gDebug.parts[GROUP_LAUNCHER];
    s->bitChips = gDebug.parts[GROUP_BITCHIP];
    for (i = 0; i < MAP_NODES; i++)
        s->nodeAdded[i] = gDebug.nodeAdded[i];
    for (i = 0; i < sizeof(s->blades); i++)
        s->blades[i] = gDebug.blades[i];
    for (i = 0; i < BLADER_ROWS; i++) {
        if (gDebug.rowFlags[i])
            s->rowFlags[i >> 3] |= 1 << (i & 7);
    }
    s->sum = Sum(s);
}

static void Unpack(const struct SavedDebug *s)
{
    u32 i;

    const struct SavedAbilities *a = Abilities(s);

    for (i = 0; i < DBG_SAVED_ITEMS; i++) {
        s32 lo;
        s32 hi;

        DebugItemRange(i, &lo, &hi);
        if (s->value[i] >= lo && s->value[i] <= hi)
            gDebug.value[i] = s->value[i];
    }
    if (a->tag == ABILITY_TAG && a->sum == AbilitySum(a)) {
        for (i = 0; i < DBG_ABILITY_COUNT; i++)
            gDebug.value[DBG_ABILITY_FIRST + i] = (a->on >> i) & 1;
    }
    if (Weather(s)->tag == WEATHER_TAG && Weather(s)->sum == WeatherSum(Weather(s))
        && Weather(s)->value < WEATHER_COUNT)
        gDebug.value[DBG_WEATHER] = Weather(s)->value;
    if (Stadium(s)->tag == STADIUM_TAG && Stadium(s)->sum == StadiumSum(Stadium(s))
        && Stadium(s)->value < STADIUM_COUNT)
        gDebug.value[DBG_STADIUM] = Stadium(s)->value;
    gDebug.hasStrength = (s->has & HAS_STRENGTH) != 0;
    gDebug.hasExp = (s->has & HAS_EXP) != 0;
    gDebug.hasCredits = (s->has & HAS_CREDITS) != 0;
    gDebug.charactersOn = (s->has & ON_CHARACTERS) != 0;
    gDebug.bladesOn = (s->has & ON_BLADES) != 0;
    gDebug.partsOn = (s->has & ON_PARTS) != 0;
    gDebug.locationsOn = (s->has & ON_LOCATIONS) != 0;
    gDebug.strength = s->strength;
    gDebug.exp = s->exp;
    gDebug.credits = s->credits;
    gDebug.parts[GROUP_RIPCORD] = s->ripcords;
    gDebug.parts[GROUP_LAUNCHER] = s->launchers;
    gDebug.parts[GROUP_BITCHIP] = s->bitChips;
    for (i = 0; i < MAP_NODES; i++)
        gDebug.nodeAdded[i] = s->nodeAdded[i];
    for (i = 0; i < sizeof(s->blades); i++)
        gDebug.blades[i] = s->blades[i];
    for (i = 0; i < BLADER_ROWS; i++)
        gDebug.rowFlags[i] = (s->rowFlags[i >> 3] >> (i & 7)) & 1;
}

/* Replaces the bl to sub_08044F14 (write the slot's data blocks) in the save
 * commit sub_08044DAC. Retail's result is returned unchanged: it is nonzero
 * when the slot was written, and the record is only written after that. A
 * block that already holds its bytes is not programmed again. */
s32 DebugSaveBlocks(u32 slot, void *image)
{
    u32 buf[(DBG_SAVE_BYTES + 3) / 4];
    u32 i;
    s32 result = sub_08044F14(slot, image);

    if (result == 0 || gDebug.magic != DBG_MAGIC)
        return result;
    Pack((struct SavedDebug *)buf);
    for (i = 0; i < SAVE_BLOCKS; i++) {
        u32 n;

        for (n = 0; n < RETRIES; n++) {
            if (sub_080677A8(DBG_SAVE_BLOCK + i, &buf[i * 2]) == 0)
                break;
            sub_08067634(DBG_SAVE_BLOCK + i, (u32)&buf[i * 2]);
        }
    }
    return result;
}

/* Replaces the bl SaveDataRead in sub_08045128 (loading the slot). Entries
 * start off, then the saved record is applied if it is intact. */
void DebugSaveRead(void *slot, u8 fresh)
{
    u32 buf[(DBG_SAVE_BYTES + 3) / 4];
    u32 i;

    SaveDataRead((struct Unk45198Save *)slot, fresh);

    gDebug.magic = 0;
    DebugStateInit();
    for (i = 0; i < SAVE_BLOCKS; i++) {
        u32 n;

        for (n = 0; n < RETRIES; n++) {
            if (sub_08067584(DBG_SAVE_BLOCK + i, &buf[i * 2]) == 0)
                break;
        }
        if (n == RETRIES)
            return;
    }
    if (((struct SavedDebug *)buf)->tag == SAVE_TAG && ((struct SavedDebug *)buf)->sum == Sum((struct SavedDebug *)buf))
        Unpack((struct SavedDebug *)buf);
}
