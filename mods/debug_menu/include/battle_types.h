#ifndef GUARD_DEBUG_BATTLE_TYPES_H
#define GUARD_DEBUG_BATTLE_TYPES_H

#include "global.h"

/* The parts of a battle the abilities touch. Offsets are from the retail code
 * (sub_08034BE0, sub_0802FFAC, sub_080300D4, sub_080348E8); the decomp's own
 * struct Unk346C0 has no names for most of them yet. */

/* A beyblade's physics body (BattleWork+0x328 for the player, +0x37C for the
 * opponent). Positions are 24.8 fixed point, the arena is centred on
 * (0x10000, 0x10000) with a radius of about 200 units. */
struct BtlBody {
    u8 pad00[0x0C];
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
};

/* A fighter's numbers. */
struct BtlStats {
    u8 pad00[0x0C];
    s32 rpm; /* the spin shown on the HUD */
    s32 attack;
    s32 defense;
    s32 endurance; /* also what an attack or a dodge costs, halved or more */
};

/* One of the two fighters, at BattleWork+0x478 (the player) and +0x790. */
struct BtlFighter {
    struct BtlBody *body;
    struct BtlStats *stats;
    u8 pad08[0x2C8 - 0x08];
    s32 charge; /* 0..2: low, medium, high attack */
    s32 action; /* 0 attack, 1 defence, 2 and 3 bit beast moves, 5 idle */
    u8 pad2D0[0x2F8 - 0x2D0];
    s32 timer; /* frames of recovery after an action, -1 when none */
    u8 pad2FC[0x30C - 0x2FC];
    u8 index; /* 0 is the human player */
};

#define BTL_ACTION_ATTACK 0
#define BTL_ARENA_CENTER 0x10000

/* Offsets into BattleWork (gBattleWork). */
#define BTL_COLLISION 0x789 /* byte: the two bodies collided this frame */
#define BTL_GAUGE 0xBBC /* s32 per fighter: bit beast gauge */
#define BTL_GAUGE_CAP 0xBC4 /* s32 per fighter: its capacity */

typedef char BtlBodyOffsets[(u32) & ((struct BtlBody *)0)->vy == 0x1C ? 1 : -1];
typedef char BtlStatsOffsets[(u32) & ((struct BtlStats *)0)->endurance == 0x18 ? 1 : -1];
typedef char BtlFighterTimer[(u32) & ((struct BtlFighter *)0)->timer == 0x2F8 ? 1 : -1];
typedef char BtlFighterAction[(u32) & ((struct BtlFighter *)0)->action == 0x2CC ? 1 : -1];
typedef char BtlFighterIndex[(u32) & ((struct BtlFighter *)0)->index == 0x30C ? 1 : -1];

#endif
