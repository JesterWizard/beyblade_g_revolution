#ifndef GUARD_RAM_MAP_H
#define GUARD_RAM_MAP_H

#include "gba/types.h"
#include "ram_map_pool.h"

/* Hand-maintained symbols (see asm/ram_map_iwram.s). */

#define gMainWorkPtr     0x03000198
#define gBattleWork      0x03000290
#define gBattlerArena    0x03004060
#define gBattlerArenaEnd 0x0300416C

extern char gNoCashPrintBuf[];

#endif /* GUARD_RAM_MAP_H */
