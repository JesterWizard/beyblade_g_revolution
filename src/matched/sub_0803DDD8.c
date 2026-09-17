#include "global.h"

// @ 0x0803ddd8
__attribute__((naked))
void sub_0803DDD8(void)
{
    asm(".syntax unified\nldr r1, _0803DDF4 @ =0x0807AEFC\nsubs r0, #0x01\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r1, _0803DDF8 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _0803DDFC @ =0x00001818\nadds r1, r1, r2\nldr r2, [r0, #0x00]\nldrb r1, [r1, #0x00]\nlsls r0, r1, #0x02\nadds r0, r0, r2\nldr r0, [r0, #0x00]\nbx lr\n_0803DDF4: .4byte 0x0807AEFC\n_0803DDF8: .4byte 0x03000198\n_0803DDFC: .4byte 0x00001818");
}
