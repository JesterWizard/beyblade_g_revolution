#include "global.h"

// @ 0x080424e8
__attribute__((naked))
void sub_080424E8(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r4, _0804252C @ =0x03000198\nldr r2, [r4, #0x00]\nldr r1, _08042530 @ =0x0000182C\nadds r0, r2, r1\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _08042526\nmovs r3, #0x91\nlsls r3, r3, #0x03\nadds r0, r2, r3\nmovs r1, #0x00\nstr r1, [r0, #0x00]\nadds r3, #0x04\nadds r0, r2, r3\nstr r1, [r0, #0x00]\nbl sub_080427E8\nldr r0, [r4, #0x00]\nldr r1, _08042534 @ =0x000017B4\nadds r2, r0, r1\nldr r3, _08042538 @ =0x0000044C\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x00]\nldr r2, _0804253C @ =0x000017B8\nadds r1, r0, r2\nadds r3, #0x04\nadds r0, r0, r3\nldr r0, [r0, #0x00]\nstr r0, [r1, #0x00]\n_08042526:\npop {r4}\npop {r0}\nbx r0\n_0804252C: .4byte 0x03000198\n_08042530: .4byte 0x0000182C\n_08042534: .4byte 0x000017B4\n_08042538: .4byte 0x0000044C\n_0804253C: .4byte 0x000017B8");
}
