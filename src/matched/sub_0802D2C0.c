#include "global.h"

// @ 0x0802d2c0
__attribute__((naked))
void sub_0802D2C0(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r2, _0802D308 @ =0x0807741C\nldr r0, _0802D30C @ =0x03000198\nldr r1, [r0, #0x00]\nldr r3, _0802D310 @ =0x000015C8\nadds r0, r1, r3\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\nlsls r0, r0, #0x02\nadds r0, r0, r2\nldr r3, [r0, #0x00]\nldr r4, _0802D314 @ =0x000015CA\nadds r0, r1, r4\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\nlsls r0, r0, #0x04\nadds r3, r3, r0\nldr r2, _0802D318 @ =0x000015D0\nadds r0, r1, r2\nadds r4, #0x08\nadds r1, r1, r4\nmovs r4, #0x00\nldsh r2, [r0, r4]\nmovs r4, #0x00\nldsh r0, [r1, r4]\ncmp r2, r0\nble _0802D31C\nmovs r0, #0x01\nldsb r0, [r3, r0]\nlsls r0, r0, #0x10\nlsrs r0, r0, #0x10\nbl _0802D058\nb _0802D326\n_0802D308: .4byte 0x0807741C\n_0802D30C: .4byte 0x03000198\n_0802D310: .4byte 0x000015C8\n_0802D314: .4byte 0x000015CA\n_0802D318: .4byte 0x000015D0\n_0802D31C:\ncmp r2, r0\nbge _0802D326\nmovs r0, #0x00\nbl _0802D058\n_0802D326:\npop {r4}\npop {r1}\nbx r1");
}
