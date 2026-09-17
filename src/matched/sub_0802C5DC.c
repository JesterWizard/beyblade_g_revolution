#include "global.h"

// @ 0x0802c5dc
__attribute__((naked))
void sub_0802C5DC(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nlsls r0, r0, #0x18\nlsrs r1, r0, #0x18\nldr r4, _0802C614 @ =0x03000198\nldr r0, [r4, #0x00]\nldr r3, _0802C618 @ =0x00001694\nadds r0, r0, r3\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0802C622\nmovs r2, #0x00\nlsls r0, r1, #0x18\nadds r6, r4, #0x0\nadds r5, r3, #0x0\nasrs r3, r0, #0x18\nmovs r4, #0x01\n_0802C5FC:\nldr r0, [r6, #0x00]\nadds r0, r0, r5\nldr r1, [r0, #0x00]\nlsls r0, r2, #0x02\nadds r1, r0, r1\nmovs r0, #0x03\nldsb r0, [r1, r0]\ncmp r0, r3\nbne _0802C61C\nstrb r4, [r1, #0x01]\nmovs r0, #0x01\nb _0802C624\n_0802C614: .4byte 0x03000198\n_0802C618: .4byte 0x00001694\n_0802C61C:\nadds r2, #0x01\ncmp r2, #0x7F\nble _0802C5FC\n_0802C622:\nmovs r0, #0x00\n_0802C624:\npop {r4, r5, r6}\npop {r1}\nbx r1");
}
