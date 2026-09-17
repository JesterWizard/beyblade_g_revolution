#include "global.h"

// @ 0x0803dd60
__attribute__((naked))
void sub_0803DD60(void)
{
    asm(".syntax unified\nldr r2, _0803DD7C @ =0x0807B0C4\nldr r1, _0803DD80 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r3, _0803DD84 @ =0x00001818\nadds r1, r1, r3\nldrb r1, [r1, #0x00]\nlsls r1, r1, #0x02\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nbx lr\n.byte 0x00, 0x00\n_0803DD7C: .4byte 0x0807B0C4\n_0803DD80: .4byte 0x03000198\n_0803DD84: .4byte 0x00001818");
}
