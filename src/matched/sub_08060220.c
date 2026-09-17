#include "global.h"

// @ 0x08060220
__attribute__((naked))
void sub_08060220(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nldr r6, _0806024C @ =0x03000198\nldr r1, [r6, #0x00]\nlsls r4, r0, #0x02\nldr r0, _08060250 @ =0x00001710\nadds r1, r1, r0\nadds r1, r1, r4\nldr r0, [r1, #0x00]\nmovs r5, #0x01\nnegs r5, r5\ncmp r0, r5\nbeq _08060246\nbl sub_08071F84\nldr r0, [r6, #0x00]\nldr r1, _08060250 @ =0x00001710\nadds r0, r0, r1\nadds r0, r0, r4\nstr r5, [r0, #0x00]\n_08060246:\npop {r4, r5, r6}\npop {r0}\nbx r0\n_0806024C: .4byte 0x03000198\n_08060250: .4byte 0x00001710");
}
