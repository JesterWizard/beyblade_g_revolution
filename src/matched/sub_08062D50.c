#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062d50
#include "global.h"

// @ 0x08062d50
/* match-compiler: old_agbcc */
// Pack an RGB byte triple into BGR555 and store it at BG palette entry idx.
// Same shape as sub_08062CF4: `pal` hoists the base (0x05000000 materialises as
// `movs r5,#0xA0; lsls r5,#0x13`) and `mask` gives the three 0x1F constants
// retail reuses. agbcc picks r6 for the base and r5 for the byte temp, so
// old_agbcc is required for the r5/r6 split.
void sub_08062D50(u8 idx, u8 *rgb)
{
    u16 *pal;
    u16 c;
    u32 mask;

    pal = (u16 *)0x05000000;
    mask = 0x1F;
    c = (rgb[0] & mask) | ((rgb[1] & mask) << 5) | ((rgb[2] & mask) << 10);
    pal[idx] = c;
}

