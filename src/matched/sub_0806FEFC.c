#include "global.h"

// @ 0x0806fefc
__attribute__((naked))
void sub_0806FEFC(void)
{
    asm(".syntax unified\nldr r2, _0806FF20 @ =0x030040A8\nldr r1, [r2, #0x00]\ncmp r1, #0x00\nbeq _0806FF1C\nldr r0, [r1, #0x04]\nstr r0, [r2, #0x00]\nldr r2, _0806FF24 @ =0x030040B8\nldr r0, [r2, #0x00]\ncmp r0, #0x00\nbeq _0806FF12\nstr r1, [r0, #0x00]\n_0806FF12:\nldr r0, [r2, #0x00]\nstr r0, [r1, #0x04]\nmovs r0, #0x00\nstr r0, [r1, #0x00]\nstr r1, [r2, #0x00]\n_0806FF1C:\nadds r0, r1, #0x0\nbx lr\n_0806FF20: .4byte 0x030040A8\n_0806FF24: .4byte 0x030040B8");
}
