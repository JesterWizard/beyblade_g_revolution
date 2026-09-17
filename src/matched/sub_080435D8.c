#include "global.h"

// @ 0x080435d8
__attribute__((naked))
void sub_080435D8(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r4, _08043620 @ =0x03000558\nldr r2, _08043624 @ =0x08094BB4\nldr r0, _08043628 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0804362C @ =0x000017F7\nadds r3, r0, r1\nmovs r1, #0x00\nldsb r1, [r3, r1]\nlsls r1, r1, #0x02\nadds r1, r1, r2\nldr r2, _08043630 @ =0x000017F6\nadds r5, r0, r2\nmovs r0, #0x00\nldsb r0, [r5, r0]\nldr r1, [r1, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r4, #0x00]\nmovs r0, #0x00\nldsb r0, [r3, r0]\ncmp r0, #0x00\nbne _0804361A\nldr r0, _08043634 @ =0x03000554\nldr r2, [r0, #0x00]\nmovs r1, #0x00\nldsb r1, [r5, r1]\nadds r0, r2, #0x0\nadds r0, #0x08\nadds r0, r0, r1\nldrb r0, [r0, #0x00]\nstrb r0, [r2, #0x02]\n_0804361A:\npop {r4, r5}\npop {r0}\nbx r0\n_08043620: .4byte 0x03000558\n_08043624: .4byte 0x08094BB4\n_08043628: .4byte 0x03000198\n_0804362C: .4byte 0x000017F7\n_08043630: .4byte 0x000017F6\n_08043634: .4byte 0x03000554");
}
