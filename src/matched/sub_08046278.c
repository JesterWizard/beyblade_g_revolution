#include "global.h"

// @ 0x08046278
__attribute__((naked))
void BtlInitUnk16B0Slots(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r9\nmov r6, r8\npush {r6, r7}\nldr r0, _080462C4 @ =0x03000198\nmov r8, r0\nldr r1, _080462C8 @ =0x000016B0\nmov r12, r1\nmovs r4, #0x01\nnegs r4, r4\nmovs r2, #0x00\nmov r9, r2\nldr r6, _080462CC @ =0x000016B4\nldr r5, _080462D0 @ =0x000016B8\nmovs r3, #0x01\n_08046296:\nmov r7, r8\nldr r0, [r7, #0x00]\nmov r7, r12\nadds r1, r0, r7\nadds r1, r1, r2\nmov r7, r9\nstr r7, [r1, #0x00]\nadds r1, r0, r6\nadds r1, r1, r2\nstr r4, [r1, #0x00]\nadds r0, r0, r5\nadds r0, r0, r2\nstr r4, [r0, #0x00]\nadds r2, #0x0C\nsubs r3, #0x01\ncmp r3, #0x00\nbge _08046296\npop {r3, r4}\nmov r8, r3\nmov r9, r4\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n_080462C4: .4byte 0x03000198\n_080462C8: .4byte 0x000016B0\n_080462CC: .4byte 0x000016B4\n_080462D0: .4byte 0x000016B8");
}
