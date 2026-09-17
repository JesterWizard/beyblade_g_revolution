#include "global.h"

// @ 0x080601c4
__attribute__((naked))
void sub_080601C4(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r8\npush {r7}\nadds r4, r0, #0x0\nadds r6, r1, #0x0\nldr r0, _08060214 @ =0x03000198\nmov r8, r0\nldr r0, [r0, #0x00]\nlsls r5, r4, #0x02\nldr r7, _08060218 @ =0x00001710\nadds r0, r0, r7\nadds r0, r0, r5\nldr r1, [r0, #0x00]\nmovs r0, #0x01\nnegs r0, r0\ncmp r1, r0\nbeq _080601EC\nadds r0, r1, #0x0\nbl sub_08071F84\n_080601EC:\nadds r0, r4, #0x0\nadds r1, r6, #0x0\nbl sub_080720F0\nmov r1, r8\nldr r2, [r1, #0x00]\nadds r1, r2, r7\nadds r1, r1, r5\nstr r0, [r1, #0x00]\nldr r1, _0806021C @ =0x0000181A\nadds r2, r2, r1\nldrb r1, [r2, #0x00]\nbl sub_08071FC8\npop {r3}\nmov r8, r3\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08060214: .4byte 0x03000198\n_08060218: .4byte 0x00001710\n_0806021C: .4byte 0x0000181A");
}
