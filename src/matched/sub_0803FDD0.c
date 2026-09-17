#include "global.h"

// @ 0x0803fdd0
__attribute__((naked))
void sub_0803FDD0(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nlsls r0, r0, #0x10\nasrs r0, r0, #0x10\nbl sub_080405E8\nmovs r0, #0x02\nbl sub_08066390\nldr r5, _0803FE08 @ =0x03000198\nldr r4, [r5, #0x00]\nmovs r0, #0xA6\nlsls r0, r0, #0x03\nadds r4, r4, r0\nbl sub_0806639C\nadds r1, r0, #0x0\nadds r0, r4, #0x0\nbl sub_0804109C\nldr r0, [r5, #0x00]\nldr r1, _0803FE0C @ =0x0000181C\nadds r0, r0, r1\nmovs r1, #0x03\nstrb r1, [r0, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0803FE08: .4byte 0x03000198\n_0803FE0C: .4byte 0x0000181C");
}
