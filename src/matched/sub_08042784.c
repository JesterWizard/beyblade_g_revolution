#include "global.h"

// @ 0x08042784
__attribute__((naked))
void sub_08042784(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r2, r0, #0x0\nldr r0, _080427DC @ =0x03000538\nldr r0, [r0, #0x00]\nmov r12, r0\nmovs r3, #0x01\nldsb r3, [r0, r3]\nldr r0, _080427E0 @ =0x03000198\nldr r4, [r0, #0x00]\nldr r1, _080427E4 @ =0x0000182C\nadds r0, r4, r1\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _080427D6\nlsls r1, r3, #0x01\nmov r0, r12\nadds r0, #0x04\nadds r0, r0, r1\nstrh r2, [r0, #0x00]\nlsls r2, r3, #0x02\nmov r0, r12\nadds r0, #0x44\nadds r0, r0, r2\nmovs r5, #0xDC\nlsls r5, r5, #0x02\nadds r1, r4, r5\nldr r1, [r1, #0x00]\nstr r1, [r0, #0x00]\nmov r0, r12\nadds r0, #0xC4\nadds r0, r0, r2\nmovs r2, #0xDD\nlsls r2, r2, #0x02\nadds r1, r4, r2\nldr r1, [r1, #0x00]\nstr r1, [r0, #0x00]\nadds r3, #0x01\nmovs r0, #0x1F\nands r3, r0\nmov r5, r12\nstrb r3, [r5, #0x01]\n_080427D6:\npop {r4, r5}\npop {r0}\nbx r0\n_080427DC: .4byte 0x03000538\n_080427E0: .4byte 0x03000198\n_080427E4: .4byte 0x0000182C");
}
