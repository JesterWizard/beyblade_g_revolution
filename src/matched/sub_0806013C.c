#include "global.h"

// @ 0x0806013c
__attribute__((naked))
void sub_0806013C(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r5, _0806016C @ =0x03000198\nldr r0, [r5, #0x00]\nldr r1, _08060170 @ =0x0000177C\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nmovs r4, #0x01\nnegs r4, r4\ncmp r0, r4\nbeq _08060164\nbl sub_08071F84\nldr r0, [r5, #0x00]\nldr r2, _08060170 @ =0x0000177C\nadds r1, r0, r2\nstr r4, [r1, #0x00]\nmovs r1, #0xBC\nlsls r1, r1, #0x05\nadds r0, r0, r1\nstr r4, [r0, #0x00]\n_08060164:\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0806016C: .4byte 0x03000198\n_08060170: .4byte 0x0000177C");
}
