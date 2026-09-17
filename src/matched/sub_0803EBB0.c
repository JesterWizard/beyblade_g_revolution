#include "global.h"

// @ 0x0803ebb0
__attribute__((naked))
void sub_0803EBB0(void)
{
    asm(".syntax unified\nldr r2, _0803EBCC @ =0x0807B6DC\nldr r1, _0803EBD0 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r3, _0803EBD4 @ =0x00001818\nadds r1, r1, r3\nldrb r1, [r1, #0x00]\nlsls r1, r1, #0x02\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nbx lr\n.byte 0x00, 0x00\n_0803EBCC: .4byte 0x0807B6DC\n_0803EBD0: .4byte 0x03000198\n_0803EBD4: .4byte 0x00001818");
}
