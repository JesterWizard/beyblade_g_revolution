#include "global.h"

// @ 0x0802c55c
__attribute__((naked))
void sub_0802C55C(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nlsls r0, r0, #0x10\nlsrs r7, r0, #0x10\nlsls r1, r1, #0x18\nlsrs r1, r1, #0x18\nmov r12, r1\nlsls r2, r2, #0x10\nasrs r4, r2, #0x10\ncmp r4, #0x7F\nbgt _0802C5CE\nldr r6, _0802C5D4 @ =0x03000198\nldr r0, [r6, #0x00]\nldr r5, _0802C5D8 @ =0x00001694\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nlsls r2, r4, #0x02\nadds r3, r2, r0\nmovs r1, #0x00\nldsb r1, [r3, r1]\nlsls r0, r7, #0x10\nasrs r0, r0, #0x10\ncmp r1, r0\nbne _0802C5CE\nmovs r7, #0x03\nldsb r7, [r3, r7]\nmov r1, r12\nlsls r0, r1, #0x18\nasrs r0, r0, #0x18\ncmp r7, r0\nbne _0802C5CE\nmovs r1, #0xFF\nldrb r0, [r3, #0x00]\norrs r0, r1\nstrb r0, [r3, #0x00]\nldr r0, [r6, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r2, r0\nldrb r3, [r0, #0x03]\norrs r1, r3\nstrb r1, [r0, #0x03]\nldr r0, [r6, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r2, r0\nmovs r1, #0x00\nstrb r1, [r0, #0x02]\nldr r0, [r6, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r2, r0\nstrb r1, [r0, #0x01]\ncmp r7, #0x01\nbne _0802C5CE\nadds r0, r4, #0x0\nbl sub_0803E0CC\n_0802C5CE:\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n_0802C5D4: .4byte 0x03000198\n_0802C5D8: .4byte 0x00001694");
}
