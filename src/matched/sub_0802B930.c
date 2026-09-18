#include "global.h"

// @ 0x0802b930
__attribute__((naked))
void sub_0802B930(void)
{
    asm(".syntax unified\npush {r4, lr}\nadds r3, r0, #0x0\nmovs r2, #0x00\nldr r1, _0802B944 @ =0x08075AB8\n_0802B938:\nmovs r4, #0x04\nldsh r0, [r1, r4]\ncmp r0, r3\nbne _0802B948\nldr r0, [r1, #0x00]\nb _0802B954\n_0802B944: .4byte 0x08075AB8\n_0802B948:\nadds r1, #0x1C\nadds r2, #0x01\ncmp r2, #0x3D\nble _0802B938\nmovs r0, #0x01\nnegs r0, r0\n_0802B954:\npop {r4}\npop {r1}\nbx r1");
}
