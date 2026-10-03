#ifndef GUARD_FINISHERS_H
#define GUARD_FINISHERS_H

#include "global.h"

/* The parts of a battle this mod touches. Offsets are from the retail code
 * (sub_08032A88, sub_0802FFAC, sub_08034618, sub_08035984, sub_08035C64). */

/* A beyblade's physics body (BattleWork+0x328 for the player, +0x37C for the
 * opponent). Positions are 24.8 fixed point, the arena is centred on
 * (0x10000, 0x10000) with a wall at a radius of about 200 units. The step
 * (sub_08035984) clamps vx and vy to +/-0x1000 and adds az (gravity, -256) to vz
 * every frame. */
struct FinBody {
    u8 pad00[0x0C];
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
};

/* A fighter's numbers. */
struct FinStats {
    u8 pad00[0x0C];
    s32 rpm;
};

/* One of the two fighters, at BattleWork+0x478 (the player) and +0x790. */
struct FinFighter {
    struct FinBody *body;
    struct FinStats *stats;
    u8 pad08[0x2B8 - 0x08];
    s32 damage; /* what a hit did beyond the blade's endurance; 100 * damage / maxRpm is the blade's wear in percent */
    u8 pad2BC[0x2C8 - 0x2BC];
    s32 charge; /* 0..2: low, medium (green), high (red) attack */
    s32 action; /* 0 attack, 1 defence, 5 idle */
    u8 pad2D0[0x2F4 - 0x2D0];
    s32 maxRpm; /* the spin the fighter started with */
    u8 pad2F8[0x30C - 0x2F8];
    u8 index; /* 0 is the human player */
};

#define FIN_ACTION_ATTACK 0
#define FIN_P_OFFSET 0x478
#define FIN_O_OFFSET 0x790

typedef char FinFighterDamage[(u32) & ((struct FinFighter *)0)->damage == 0x2B8 ? 1 : -1];
typedef char FinFighterCharge[(u32) & ((struct FinFighter *)0)->charge == 0x2C8 ? 1 : -1];
typedef char FinFighterMax[(u32) & ((struct FinFighter *)0)->maxRpm == 0x2F4 ? 1 : -1];
typedef char FinFighterIndex[(u32) & ((struct FinFighter *)0)->index == 0x30C ? 1 : -1];
typedef char FinBodyVz[(u32) & ((struct FinBody *)0)->vz == 0x20 ? 1 : -1];

#endif
