#include "global.h"

// @ 0x080428c4
__attribute__((naked))
void sub_080428C4(void)
{
    asm(".syntax unified\nldr r0, _080428E4 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _080428E8 @ =0x00001808\nadds r0, r0, r1\nldr r2, [r0, #0x00]\nmovs r0, #0x80\nlsls r0, r0, #0x06\nands r2, r0\ncmp r2, #0x00\nbne _080428E2\nldr r0, _080428EC @ =0x03000538\nldr r1, [r0, #0x00]\nstrb r2, [r1, #0x00]\nldr r0, [r0, #0x00]\nstrb r2, [r0, #0x01]\n_080428E2:\nbx lr\n_080428E4: .4byte 0x03000198\n_080428E8: .4byte 0x00001808\n_080428EC: .4byte 0x03000538");
}
