#include "global.h"

// @ 0x0803e1f4
__attribute__((naked))
void sub_0803E1F4(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmovs r4, #0x00\nldr r2, _0803E238 @ =0x03000198\nldr r2, [r2, #0x00]\nlsls r1, r1, #0x10\nasrs r1, r1, #0x10\nmov r12, r1\nlsls r0, r0, #0x10\nasrs r6, r0, #0x10\nadds r3, r2, #0x0\nmovs r1, #0x00\nldr r0, _0803E23C @ =0x0000087C\nadds r5, r3, r0\n_0803E20E:\nldr r7, _0803E240 @ =0x000008F3\nadds r0, r3, r7\nldrb r0, [r0, #0x00]\ncmp r0, r12\nbne _0803E244\nsubs r7, #0x07\nadds r0, r3, r7\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, r6\nbne _0803E244\nadds r0, r5, r4\nldrb r0, [r0, #0x00]\ncmp r0, #0x01\nbne _0803E244\nmovs r3, #0x8D\nlsls r3, r3, #0x04\nadds r0, r1, r3\nadds r0, r2, r0\nb _0803E250\n_0803E238: .4byte 0x03000198\n_0803E23C: .4byte 0x0000087C\n_0803E240: .4byte 0x000008F3\n_0803E244:\nadds r3, #0x28\nadds r1, #0x28\nadds r4, #0x01\ncmp r4, #0x52\nble _0803E20E\nmovs r0, #0x00\n_0803E250:\npop {r4, r5, r6, r7}\npop {r1}\nbx r1");
}
