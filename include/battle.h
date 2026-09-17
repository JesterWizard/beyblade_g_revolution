#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include "global.h"
#include "ram_map.h"

/*
 * Battle subsystem IWRAM — addresses are #defined in ram_map.h.
 * See documentation/battle.md for roles.
 */

#define BTL_MAIN_WORK_FIELD_1800 0x1800
#define BTL_MAIN_WORK_FIELD_1818 0x1818

struct BtlObjNode {
    struct BtlObjNode *next;
    struct BtlObjNode *prev;
};

struct BattleWork {
    u8 *base; /* *(u8 **)gBattleWork */
};

#endif /* GUARD_BATTLE_H */
