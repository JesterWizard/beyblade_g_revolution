#include "global.h"

// @ 0x0802e2f8
__attribute__((naked))
void sub_0802E2F8(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadds r5, r2, #0x0\nlsls r0, r0, #0x10\nlsrs r2, r0, #0x10\nlsls r1, r1, #0x10\nlsrs r4, r1, #0x10\nldr r3, _0802E34C @ =0x08077AC0\nmovs r1, #0x00\nldsh r0, [r3, r1]\nmovs r1, #0x01\nnegs r1, r1\nmov r12, r3\ncmp r0, r1\nble _0802E35E\nlsls r0, r2, #0x10\nasrs r2, r0, #0x10\nadds r6, r1, #0x0\nmovs r1, #0x00\nlsls r0, r4, #0x10\nasrs r4, r0, #0x10\n_0802E320:\nadds r3, r1, r3\nmovs r7, #0x00\nldsh r0, [r3, r7]\ncmp r0, r2\nbne _0802E350\nmovs r7, #0x02\nldsh r0, [r3, r7]\ncmp r0, r4\nbne _0802E350\nldrh r3, [r3, #0x06]\nlsls r0, r3, #0x10\ncmp r0, #0x00\nble _0802E350\nasrs r0, r0, #0x11\nmuls r0, r5\nmovs r1, #0x64\nbl _080740B0\ncmp r0, #0x00\nbgt _0802E360\nmovs r0, #0x02\nb _0802E360\n_0802E34C: .4byte 0x08077AC0\n_0802E350:\nadds r1, #0x0C\nmov r3, r12\nadds r0, r1, r3\nmovs r7, #0x00\nldsh r0, [r0, r7]\ncmp r0, r6\nbgt _0802E320\n_0802E35E:\nmovs r0, #0x0A\n_0802E360:\npop {r4, r5, r6, r7}\npop {r1}\nbx r1");
}
