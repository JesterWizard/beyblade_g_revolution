#include "global.h"

// @ 0x0803dd88
__attribute__((naked))
s32 sub_0803DD88(s32 a)
{
    asm(".syntax unified\nldr r3, _0803DDA4 @ =0x0807A1F4\nldr r1, _0803DDA8 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _0803DDAC @ =0x00001818\nadds r1, r1, r2\nldrb r1, [r1, #0x00]\nlsls r2, r1, #0x02\nlsls r1, r0, #0x02\nadds r1, r1, r0\nlsls r1, r1, #0x03\nadds r2, r2, r1\nadds r2, r2, r3\nldr r0, [r2, #0x00]\nbx lr\n_0803DDA4: .4byte 0x0807A1F4\n_0803DDA8: .4byte 0x03000198\n_0803DDAC: .4byte 0x00001818");
}
