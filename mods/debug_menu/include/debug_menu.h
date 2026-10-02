#ifndef GUARD_DEBUG_MENU_H
#define GUARD_DEBUG_MENU_H

#include "global.h"
#include "bgm.h"

/* Menu rows, in display order. */
enum DebugItem {
    DBG_MAX_RPM,
    DBG_MAX_STR,
    DBG_MAX_EXP,
    DBG_MAX_LEVEL,
    DBG_MAX_CREDITS,
    DBG_ALL_BEYBLADES,
    DBG_ALL_PARTS,
    DBG_ALL_CHARACTERS,
    DBG_ALL_LOCATIONS,
    DBG_MAX_BITBEAST_EXP,
    DBG_INF_BEYBLADE_HEALTH,
    DBG_INF_RIPCORD,
    DBG_INF_LAUNCHER,
    DBG_MOVE_SPEED,
    DBG_BGM,
    DBG_CHARACTER,
    DBG_ITEM_COUNT
};

#define DBG_MAGIC 0xDB6C0DE1

#define BLADER_ROWS 55 /* BeybladeCollectionEntry rows */
#define BEYBLADE_IDS 83 /* beyblade templates, inventory group 1 */
#define PART_GROUPS 9 /* inventory groups 0..8; 1 is beyblades */
#define MAX_MOVE_SPEED 4

/* Everything the menu and the cheats remember. It lives at the top of EWRAM,
 * a page the retail heap no longer owns (see hooks.txt), at gDebug. */
struct DebugState {
    u32 magic;
    u8 value[DBG_ITEM_COUNT]; /* 0/1 for toggles, the setting for the others */
    u8 cursor;
    u8 top;

    /* Cheat bookkeeping: what was changed, so turning an entry off restores it. */
    u8 savedStrength;
    u8 savedExp;
    u8 savedCredits;
    u8 hasStrength;
    u8 hasExp;
    u8 hasCredits;
    s8 strength;
    s16 exp;
    u32 credits;
    u8 touchedRow[BLADER_ROWS];
    s16 rowExp[BLADER_ROWS];
    u8 rowFlags[BLADER_ROWS];
    u8 charactersOn;
    u8 blades[(BEYBLADE_IDS + 7) / 8]; /* beyblades this cheat added */
    u16 parts[PART_GROUPS]; /* per group: bit k = id k added */
    u8 bladesOn;
    u8 partsOn;
};

extern struct DebugState gDebug;

/* Display name of a track, or "?" when out of range. */
const char *BgmName(unsigned int track);

void DebugStateInit(void);
void CheatsTick(void);
void CheatsOnToggle(u32 item);
void CheatsOnChange(u32 item);

#endif
