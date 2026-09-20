#include "global.h"

// @ 0x0803ecb8
__attribute__((naked))
void sub_0803ECB8(void)
{
    asm(".syntax unified\nldr r2, _0803ECD4 @ =0x0807BDA4\nldr r1, _0803ECD8 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r3, _0803ECDC @ =0x00001818\nadds r1, r1, r3\nldrb r1, [r1, #0x00]\nlsls r1, r1, #0x02\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nbx lr\n.byte 0x00, 0x00\n_0803ECD4: .4byte 0x0807BDA4\n_0803ECD8: .4byte 0x03000198\n_0803ECDC: .4byte 0x00001818");
}
