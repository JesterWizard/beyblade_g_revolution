#include "global.h"

// @ 0x08041f88
__attribute__((naked))
void sub_08041F88(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r4, _08041FCC @ =0x03000198\nldr r1, [r4, #0x00]\nmovs r2, #0xEB\nlsls r2, r2, #0x02\nadds r0, r1, r2\nmovs r2, #0x00\nstr r2, [r0, #0x00]\nmovs r3, #0xEC\nlsls r3, r3, #0x02\nadds r0, r1, r3\nstr r2, [r0, #0x00]\nldr r0, _08041FD0 @ =0x0000180C\nadds r1, r1, r0\nstr r2, [r1, #0x00]\nbl sub_08057274\nldr r0, [r4, #0x00]\nldr r1, _08041FD4 @ =0x00000868\nadds r2, r0, r1\nmovs r3, #0xDC\nlsls r3, r3, #0x02\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x00]\nldr r2, _08041FD8 @ =0x0000086C\nadds r1, r0, r2\nadds r3, #0x04\nadds r0, r0, r3\nldr r0, [r0, #0x00]\nstr r0, [r1, #0x00]\npop {r4}\npop {r0}\nbx r0\n_08041FCC: .4byte 0x03000198\n_08041FD0: .4byte 0x0000180C\n_08041FD4: .4byte 0x00000868\n_08041FD8: .4byte 0x0000086C");
}
