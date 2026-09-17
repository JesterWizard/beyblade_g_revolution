#include "global.h"

// @ 0x0803e258
__attribute__((naked))
void sub_0803E258(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmovs r3, #0x00\nldr r1, _0803E28C @ =0x03000198\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x10\nasrs r6, r0, #0x10\nldr r0, _0803E290 @ =0x0000087C\nadds r5, r1, r0\nadds r2, r1, #0x0\nmovs r4, #0x00\nldr r7, _0803E294 @ =0x000008EC\n_0803E26E:\nadds r0, r2, r7\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, r6\nbne _0803E298\nadds r0, r5, r3\nldrb r0, [r0, #0x00]\ncmp r0, #0x01\nbne _0803E298\nmovs r2, #0x8D\nlsls r2, r2, #0x04\nadds r0, r4, r2\nadds r0, r1, r0\nb _0803E2A4\n_0803E28C: .4byte 0x03000198\n_0803E290: .4byte 0x0000087C\n_0803E294: .4byte 0x000008EC\n_0803E298:\nadds r2, #0x28\nadds r4, #0x28\nadds r3, #0x01\ncmp r3, #0x52\nble _0803E26E\nmovs r0, #0x00\n_0803E2A4:\npop {r4, r5, r6, r7}\npop {r1}\nbx r1");
}
