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
    DBG_FULL_GAUGE,
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
#define GROUP_RIPCORD 2 /* inventory groups of the parts the menu gives */
#define GROUP_LAUNCHER 3
#define GROUP_BITCHIP 7
#define MAP_NODES 16 /* world map spots, one flag byte each */
#include "character_count.h" /* generated: every person sprite in the game */
#define TYSON_PORTRAIT 56 /* the player's own entry in the portrait tables */

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
    u8 locationsOn;
    u8 nodeAdded[MAP_NODES]; /* map flag bits this cheat set, per node */
    u8 characterOn;
};

extern struct DebugState gDebug;

/* Display name of a track, or "?" when out of range. */
const char *BgmName(unsigned int track);

/* Name of character `value` (0 = the player). */
const char *CharacterName(u32 value);

struct CharacterLook {
    u32 sprite; /* overworld walking sprite template */
    u32 palette; /* its OBJ palette (4-byte aligned, loaded into slot 0) */
    u32 portrait; /* blader portrait / name / data row index; TYSON_PORTRAIT = unnamed NPC */
    u32 npc; /* lowest scene NPC id using this sprite */
    const char *name; /* hand-given name, or 0 */
    u32 faceTemplate; /* dialogue portrait of an NPC that is no blader (portrait == TYSON_PORTRAIT), or 0 */
    u32 facePalette;
};

extern const struct CharacterLook gCharacterLooks[CHARACTER_COUNT];

void DebugStateInit(void);
void DebugItemRange(u32 item, s32 *lo, s32 *hi);
void CheatsTick(void);
void CheatsOnToggle(u32 item);
void CheatsOnChange(u32 item);

#endif
