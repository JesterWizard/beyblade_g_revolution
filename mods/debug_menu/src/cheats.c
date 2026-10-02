#include "debug_menu.h"

/* What each menu entry does. Entries that hold a value (stats, credits, bit
 * beast experience, characters) are enforced every overworld frame and
 * restored when switched off. Entries that give things (beyblades, parts)
 * act once when switched on and take back only what they added when switched
 * off. Everything lives in gDebug. */

#define MAX_STRENGTH 99
#define MAX_EXP 0x3FFF /* retail cap, see BtlApplyClampedScore */
#define LEVEL_EXP 4000 /* first experience of the top level (16) */
#define MAX_CREDITS 99999
#define MAX_BITBEAST_EXP 0x3FFF
#define MAX_LAUNCH_RPM 32767 /* largest value the retail signed spin step takes */

#define BLADER_MET 0x01 /* BeybladeCollectionEntry row, byte +7 */

/* Inventory entries are {kind (item id), slot, value (wear), group (category)}.
 * Group 1 is beyblades, groups 2 and 3 are ripcords and launchers. */
#define GROUP_BEYBLADE 1
#define GROUP_RIPCORD 2
#define GROUP_LAUNCHER 3
#define NEW_BEYBLADE_VALUE 0xFF /* "take the template", as the shop does */
#define NEW_PART_VALUE 100
#define PART_VALUE_SAFE 0x7F /* survives one wear step of kind + strength */

extern s32 CollectionAddItem(u8 kind, u8 group, u8 slot, u8 value);
extern s32 CollectionFindByGroupKind(s8 group, s8 kind, struct CollectionLookup *out);
extern s32 CollectionFindByGroupSlot(s8 group, u8 slot, struct CollectionLookup *out);
extern void CollectionFreeSlot(u16 kind, u8 group, s16 index);
extern s32 BattlePartsApplyWear(void);
extern s32 ExpBracketBase(s32 level);
extern s32 ExpBracketTop(s32 level);
extern s16 ScaleRatio(s32 a, s32 b, s32 c);
extern void _0803CECC(void);
extern void _08041E88(void *dir, s32 speed);
extern void _0805FED4(void *track);

/* The parts with a fixed catalogue: first and last id per inventory group.
 * Ripcords and launchers are numbered from 1; bit chips from 0 (Dragoon, the
 * starting chip, is group 7 id 0). Blade bases, attack rings and weight disks
 * (groups 4 to 6) are open-ended stat tables that the game hands out piece by
 * piece, so there is no complete set to give. */
#define GROUP_BITCHIP 7

struct PartRange {
    u8 group;
    u8 first;
    u8 last;
};

static const struct PartRange sParts[] = {
    {GROUP_RIPCORD, 1, 4},
    {GROUP_LAUNCHER, 1, 4},
    {GROUP_BITCHIP, 0, 6},
};

static u8 *Row(u32 i)
{
    return (u8 *)BeybladeCollectionEntry(i);
}

static s16 *RowExp(u32 i)
{
    return (s16 *)Row(i);
}

/* ---- values held while an entry is on ---------------------------------- */

static void HoldStrength(void)
{
    struct MainWork *w = gMainWorkPtr;

    if (gDebug.value[DBG_MAX_STR]) {
        if (!gDebug.hasStrength) {
            gDebug.strength = w->strength;
            gDebug.hasStrength = 1;
        }
        w->strength = MAX_STRENGTH;
    } else if (gDebug.hasStrength) {
        w->strength = gDebug.strength;
        gDebug.hasStrength = 0;
    }
}

static void HoldExp(void)
{
    struct MainWork *w = gMainWorkPtr;
    s32 want = -1;

    if (gDebug.value[DBG_MAX_LEVEL])
        want = LEVEL_EXP;
    if (gDebug.value[DBG_MAX_EXP])
        want = MAX_EXP;

    if (want >= 0) {
        if (!gDebug.hasExp) {
            gDebug.exp = w->expPoints;
            gDebug.hasExp = 1;
        }
        w->expPoints = want;
    } else if (gDebug.hasExp) {
        w->expPoints = gDebug.exp;
        gDebug.hasExp = 0;
    }
}

static void HoldCredits(void)
{
    struct MainWork *w = gMainWorkPtr;

    if (gDebug.value[DBG_MAX_CREDITS]) {
        if (!gDebug.hasCredits) {
            gDebug.credits = w->unk0870;
            gDebug.hasCredits = 1;
        }
        w->unk0870 = MAX_CREDITS;
    } else if (gDebug.hasCredits) {
        w->unk0870 = gDebug.credits;
        gDebug.hasCredits = 0;
    }
}

/* Every blader whose blade the player has collected (the rows "Meet bladers"
 * lists) gets full bit beast experience. */
static void HoldBitBeastExp(void)
{
    s32 i;

    for (i = 0; i < BLADER_ROWS; i++) {
        u8 *row = Row(i);
        bool32 want = gDebug.value[DBG_MAX_BITBEAST_EXP] && (row[7] & BLADER_MET);

        if (want) {
            if (!gDebug.touchedRow[i]) {
                gDebug.rowExp[i] = *RowExp(i);
                gDebug.touchedRow[i] = 1;
            }
            *RowExp(i) = MAX_BITBEAST_EXP;
        } else if (gDebug.touchedRow[i]) {
            *RowExp(i) = gDebug.rowExp[i];
            gDebug.touchedRow[i] = 0;
        }
    }
}

/* "Meet bladers" lists every row whose byte +7 has bit 0 set. */
static void HoldCharacters(void)
{
    s32 i;

    if (gDebug.value[DBG_ALL_CHARACTERS]) {
        if (!gDebug.charactersOn) {
            for (i = 0; i < BLADER_ROWS; i++) {
                u8 *row = Row(i);

                gDebug.rowFlags[i] = row[7] & BLADER_MET;
                row[7] |= BLADER_MET;
            }
            gDebug.charactersOn = 1;
        }
    } else if (gDebug.charactersOn) {
        for (i = 0; i < BLADER_ROWS; i++) {
            u8 *row = Row(i);

            row[7] = (row[7] & ~BLADER_MET) | gDebug.rowFlags[i];
        }
        gDebug.charactersOn = 0;
    }
}

/* ---- things given once ------------------------------------------------- */

static void GiveBeyblades(void)
{
    s32 id;

    if (gDebug.value[DBG_ALL_BEYBLADES]) {
        if (gDebug.bladesOn)
            return;
        for (id = 0; id < BEYBLADE_IDS; id++) {
            if (CollectionFindByGroupKind(GROUP_BEYBLADE, id, NULL))
                continue;
            if (CollectionAddItem(id, GROUP_BEYBLADE, 0, NEW_BEYBLADE_VALUE))
                gDebug.blades[id >> 3] |= 1 << (id & 7);
        }
        gDebug.bladesOn = 1;
    } else if (gDebug.bladesOn) {
        for (id = 0; id < BEYBLADE_IDS; id++) {
            struct CollectionLookup out;

            if (!(gDebug.blades[id >> 3] & (1 << (id & 7))))
                continue;
            if (CollectionFindByGroupKind(GROUP_BEYBLADE, id, &out))
                CollectionFreeSlot(out.kind, GROUP_BEYBLADE, out.index);
            gDebug.blades[id >> 3] &= ~(1 << (id & 7));
        }
        gDebug.bladesOn = 0;
    }
}

static void GiveParts(void)
{
    u32 r;
    s32 id;

    if (gDebug.value[DBG_ALL_PARTS]) {
        if (gDebug.partsOn)
            return;
        for (r = 0; r < sizeof(sParts) / sizeof(sParts[0]); r++) {
            for (id = sParts[r].first; id <= sParts[r].last; id++) {
                if (CollectionFindByGroupKind(sParts[r].group, id, NULL))
                    continue;
                if (CollectionAddItem(id, sParts[r].group, 0, NEW_PART_VALUE))
                    gDebug.parts[sParts[r].group] |= 1 << id;
            }
        }
        gDebug.partsOn = 1;
    } else if (gDebug.partsOn) {
        for (r = 0; r < sizeof(sParts) / sizeof(sParts[0]); r++) {
            for (id = sParts[r].first; id <= sParts[r].last; id++) {
                struct CollectionLookup out;

                if (!(gDebug.parts[sParts[r].group] & (1 << id)))
                    continue;
                if (CollectionFindByGroupKind(sParts[r].group, id, &out))
                    CollectionFreeSlot(out.kind, sParts[r].group, out.index);
                gDebug.parts[sParts[r].group] &= ~(1 << id);
            }
        }
        gDebug.partsOn = 0;
    }
}

/* ---- entry points ------------------------------------------------------ */

void CheatsTick(void)
{
    HoldStrength();
    HoldExp();
    HoldCredits();
    HoldCharacters();
    HoldBitBeastExp();
    GiveBeyblades();
    GiveParts();
}

void CheatsOnToggle(u32 item)
{
    CheatsTick();
}

/* A value entry (speed, BGM, character) was changed with left/right. */
void CheatsOnChange(u32 item)
{
    if (item == DBG_BGM)
        _0805FED4((void *)(u32)gDebug.value[DBG_BGM]);
}

/* ---- hooks into retail code -------------------------------------------- */

/* Replaces the bl to sub_08041E88 in FieldUpdateFrame. */
void DebugMoveStep(void *dir, s32 speed)
{
    _08041E88(dir, speed * gDebug.value[DBG_MOVE_SPEED]);
}

/* Replaces both bls to BattlePartsApplyWear. Retail subtracts the part id plus
 * strength from the equipped launcher and ripcord and frees a part that drops
 * to 0. Pre-loading the health keeps that from happening. */
static void KeepPart(u32 item, s8 group)
{
    struct CollectionLookup out;

    if (gDebug.value[item] && CollectionFindByGroupSlot(group, 1, &out))
        out.entry->value = PART_VALUE_SAFE;
}

static void FullPart(u32 item, s8 group)
{
    struct CollectionLookup out;

    if (gDebug.value[item] && CollectionFindByGroupSlot(group, 1, &out))
        out.entry->value = NEW_PART_VALUE;
}

s32 DebugPartsApplyWear(void)
{
    s32 worn;

    KeepPart(DBG_INF_LAUNCHER, GROUP_LAUNCHER);
    KeepPart(DBG_INF_RIPCORD, GROUP_RIPCORD);
    worn = BattlePartsApplyWear();
    FullPart(DBG_INF_LAUNCHER, GROUP_LAUNCHER);
    FullPart(DBG_INF_RIPCORD, GROUP_RIPCORD);
    return worn;
}

/* Replaces the bl to _0803CECC (the launch RPM formula). Retail leaves the
 * player's launch RPM in the battle record and copies it to the live spin and
 * its cap; do the same with the maximum. */
void DebugLaunch(void)
{
    u8 *battle;
    s32 rpm = MAX_LAUNCH_RPM;

    _0803CECC();
    if (!gDebug.value[DBG_MAX_RPM])
        return;
    battle = (u8 *)gBattleWork;
    *(s32 *)(battle + 0xBB4) = rpm;
    *(s32 *)(battle + 0xBBC) = rpm;
    *(s32 *)(battle + 0xBC4) = rpm;
    *(s32 *)(battle + 0x13C) = rpm;
    *(s32 *)(battle + 0x144) = rpm;
    *(s32 *)(0x030002A0 + 12) = rpm;
}

/* Replaces ExpBracket (sub_08042BE8). Identical, except that experience past
 * the last threshold gives the last level; retail returned -1 there, which
 * broke the HUD from 4000 experience on. */
s32 ExpBracketFixed(s32 points)
{
    s32 i;

    for (i = 0; gData_080908BC[i].level != -1; i++) {
        if (points >= gData_080908BC[i].minPoints
            && (gData_080908BC[i + 1].level == -1 || points < gData_080908BC[i + 1].minPoints))
            return gData_080908BC[i].level;
    }
    return -1;
}

/* Replaces ExpBarFill (sub_0802E1B4): a full bar on the last level, which has
 * no upper threshold. */
s8 ExpBarFillFixed(s32 points)
{
    s32 level = sub_08042BE8(points);
    s32 base = ExpBracketBase(level);
    s32 top = ExpBracketTop(level);

    if (top == -1)
        return 14;
    return 14 - ScaleRatio(top - points, top - base, 14);
}
