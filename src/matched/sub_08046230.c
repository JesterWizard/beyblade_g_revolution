#include "global.h"

// @ 0x08046230
__attribute__((naked))
void sub_08046230(void)
{
    asm(".syntax unified\npush {r4, lr}\nadds r1, r0, #0x0\ncmp r1, #0x01\nbhi _08046266\nldr r0, _0804626C @ =0x03000198\nldr r3, [r0, #0x00]\nlsls r0, r1, #0x01\nadds r0, r0, r1\nlsls r2, r0, #0x02\nldr r1, _08046270 @ =0x000016B0\nadds r0, r3, r1\nadds r1, r0, r2\nldr r0, [r1, #0x00]\ncmp r0, #0x01\nbne _08046266\nmovs r0, #0x00\nstr r0, [r1, #0x00]\nldr r4, _08046274 @ =0x000016B4\nadds r0, r3, r4\nadds r0, r0, r2\nmovs r1, #0x01\nnegs r1, r1\nstr r1, [r0, #0x00]\nadds r4, #0x04\nadds r0, r3, r4\nadds r0, r0, r2\nstr r1, [r0, #0x00]\n_08046266:\npop {r4}\npop {r0}\nbx r0\n_0804626C: .4byte 0x03000198\n_08046270: .4byte 0x000016B0\n_08046274: .4byte 0x000016B4");
}
