#include "global.h"

// @ 0x080603e0
__attribute__((naked))
void sub_080603E0(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nlsls r0, r0, #0x10\nlsrs r5, r0, #0x10\nmovs r1, #0x00\n_080603E8:\nldr r6, _0806041C @ =0x03000198\nldr r0, [r6, #0x00]\nlsls r4, r1, #0x10\nasrs r4, r4, #0x10\nlsls r1, r4, #0x02\nldr r2, _08060420 @ =0x00001710\nadds r0, r0, r2\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nadds r1, r5, #0x0\nbl sub_08071FC8\nadds r4, #0x01\nlsls r4, r4, #0x10\nlsrs r1, r4, #0x10\nasrs r4, r4, #0x10\ncmp r4, #0x18\nble _080603E8\nldr r0, [r6, #0x00]\nldr r1, _08060424 @ =0x0000181A\nadds r0, r0, r1\nstrb r5, [r0, #0x00]\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0806041C: .4byte 0x03000198\n_08060420: .4byte 0x00001710\n_08060424: .4byte 0x0000181A");
}
