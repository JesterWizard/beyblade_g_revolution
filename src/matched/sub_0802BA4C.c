#include "global.h"

// @ 0x0802ba4c
__attribute__((naked))
void sub_0802BA4C(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r4, _0802BA70 @ =0x03000268\nldr r0, [r4, #0x00]\ncmp r0, #0x00\nbeq _0802BA5E\nbl sub_0806A434\nmovs r0, #0x00\nstr r0, [r4, #0x00]\n_0802BA5E:\nldr r0, _0802BA74 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0802BA78 @ =0x00001694\nadds r0, r0, r1\nmovs r1, #0x00\nstr r1, [r0, #0x00]\npop {r4}\npop {r0}\nbx r0\n_0802BA70: .4byte 0x03000268\n_0802BA74: .4byte 0x03000198\n_0802BA78: .4byte 0x00001694");
}
