#include "global.h"
#include "data_symbols.h"

// @ 0x08069894
// Clear two byte flags, set a third to 0x20, zero four entries of the two
// per-index arrays, then kick two transfers with n = 0x100.
// The three destinations must be *distinct symbols* (gData_03000108 /
// gData_030001B0 / gData_030001A8 -- see asm/data_symbols.s): as bare literals
// agbcc folds the second address into `add r0, #0xA8` and hoists all three pool
// loads up front, losing retail's interleaved load/store shape.
void sub_08069894(void)
{
    u8 i;
    u16 zero;
    u32 n;

    gData_03000108[0] = 0;
    gData_030001B0[0] = 0;
    gData_030001A8[0] = 0x20;

    i = 0;
    zero = 0;
    while (i <= 3)
    {
        *sub_08069908(i) = zero;
        *sub_08069948(i) = zero;
        i = (u8)(i + 1);
    }

    n = 0x80;
    n <<= 1;
    sub_08069A60(2, 0, n, n);
    sub_08069A60(3, 0, n, n);
}
