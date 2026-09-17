#include "global.h"

// @ 0x08040ef4
__attribute__((naked))
void sub_08040EF4(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nadds r5, r0, #0x0\nldr r2, _08040F28 @ =0x0808B2E4\nldr r1, [r2, #0x00]\nmovs r0, #0x01\nnegs r0, r0\ncmp r1, r0\nbeq _08040F44\nmovs r4, #0x00\nadds r3, r2, #0x0\nadds r6, r2, #0x4\n_08040F0A:\nldr r0, [r3, #0x00]\ncmp r0, r5\nbne _08040F34\nadds r1, r4, r6\nldr r0, _08040F2C @ =0x03000198\nldr r0, [r0, #0x00]\nldr r2, _08040F30 @ =0x00001818\nadds r0, r0, r2\nldr r1, [r1, #0x00]\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nb _08040F46\n.byte 0x00, 0x00\n_08040F28: .4byte 0x0808B2E4\n_08040F2C: .4byte 0x03000198\n_08040F30: .4byte 0x00001818\n_08040F34:\nadds r2, #0x08\nadds r4, #0x08\nadds r3, #0x08\nldr r1, [r2, #0x00]\nmovs r0, #0x01\nnegs r0, r0\ncmp r1, r0\nbne _08040F0A\n_08040F44:\nmovs r0, #0x00\n_08040F46:\npop {r4, r5, r6}\npop {r1}\nbx r1");
}
