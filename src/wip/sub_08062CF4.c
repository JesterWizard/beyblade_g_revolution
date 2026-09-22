/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08062cf4
// Pack an RGB byte triple into BGR555 and store it as OBJ palette entry idx.
// The `pal` local hoisting the palette base is load-bearing: it keeps the base
// live across the packing so agbcc gives it r5 (retail) instead of loading it
// into a late scratch. old_agbcc is required for the r5/r6 split.
void sub_08062CF4(u8 idx, u8 *rgb)
{
    u16 *pal;
    u16 c;
    u32 mask;

    pal = gData_05000200;
    mask = 0x1F;
    c = (rgb[0] & mask) | ((rgb[1] & mask) << 5) | ((rgb[2] & mask) << 10);
    pal[idx] = c;
}
