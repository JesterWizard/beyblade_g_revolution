#include "global.h"

// @ 0x0802c2b0
__attribute__((naked))
void sub_0802C2B0(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nlsls r0, r0, #0x18\nlsrs r3, r0, #0x18\nlsls r1, r1, #0x10\nlsrs r7, r1, #0x10\nldr r1, _0802C30C @ =0x03000198\nldr r0, [r1, #0x00]\nldr r4, _0802C310 @ =0x00001694\nadds r0, r0, r4\nldr r0, [r0, #0x00]\nmov r12, r1\ncmp r0, #0x00\nbeq _0802C2F0\nmovs r2, #0x00\nlsls r0, r3, #0x18\nmov r6, r12\nadds r5, r4, #0x0\nasrs r3, r0, #0x18\nmovs r4, #0x00\n_0802C2D6:\nldr r0, [r6, #0x00]\nadds r0, r0, r5\nldr r1, [r0, #0x00]\nlsls r0, r2, #0x02\nadds r1, r0, r1\nmovs r0, #0x03\nldsb r0, [r1, r0]\ncmp r0, r3\nbne _0802C2EA\nstrb r4, [r1, #0x01]\n_0802C2EA:\nadds r2, #0x01\ncmp r2, #0x7F\nble _0802C2D6\n_0802C2F0:\nmov r1, r12\nldr r0, [r1, #0x00]\nlsls r1, r7, #0x10\nldr r2, _0802C310 @ =0x00001694\nadds r0, r0, r2\nldr r0, [r0, #0x00]\nasrs r1, r1, #0x0E\nadds r1, r1, r0\nmovs r0, #0x01\nstrb r0, [r1, #0x01]\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0802C30C: .4byte 0x03000198\n_0802C310: .4byte 0x00001694");
}
