#include "global.h"

// @ 0x08045128
__attribute__((naked))
void sub_08045128(void)
{
    asm(".syntax unified\npush {r4, lr}\nlsls r0, r0, #0x18\nlsrs r0, r0, #0x18\nldr r1, _08045168 @ =0x03000198\nldr r3, [r1, #0x00]\nldr r1, _0804516C @ =0x00001688\nadds r2, r3, r1\nlsls r1, r0, #0x01\nadds r1, r1, r0\nlsls r1, r1, #0x03\nldr r2, [r2, #0x00]\nadds r2, r2, r1\nldr r1, _08045170 @ =0x0000168C\nadds r4, r3, r1\nlsls r1, r0, #0x06\nsubs r1, r1, r0\nlsls r1, r1, #0x02\nsubs r1, r1, r0\nlsls r1, r1, #0x05\nldr r0, [r4, #0x00]\nadds r0, r0, r1\nldr r1, _08045174 @ =0x00001788\nadds r3, r3, r1\nldr r1, [r2, #0x08]\nstr r1, [r3, #0x00]\nmovs r1, #0x00\nbl sub_08045590\npop {r4}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08045168: .4byte 0x03000198\n_0804516C: .4byte 0x00001688\n_08045170: .4byte 0x0000168C\n_08045174: .4byte 0x00001788");
}
