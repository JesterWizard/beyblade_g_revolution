#include "global.h"

// @ 0x08052934
__attribute__((naked))
void sub_08052934(void)
{
    asm(".syntax unified\npush {r4, lr}\nadds r4, r0, #0x0\nlsls r4, r4, #0x18\nlsrs r4, r4, #0x14\nadds r1, r4, #0x0\nadds r1, #0x08\nmovs r0, #0x00\nbl sub_080615EC\nldr r0, _08052974 @ =0x082BCD00\nldr r1, _08052978 @ =0x080B738E\nbl sub_080617C4\nldr r0, _0805297C @ =0x080995AC\nadds r0, #0x0C\nadds r4, r4, r0\nldr r0, _08052980 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _08052984 @ =0x00001818\nadds r0, r0, r1\nldr r1, [r4, #0x00]\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nmovs r1, #0x24\nmovs r2, #0x02\nbl sub_0806171C\npop {r4}\npop {r0}\nbx r0\n_08052974: .4byte 0x082BCD00\n_08052978: .4byte 0x080B738E\n_0805297C: .4byte 0x080995AC\n_08052980: .4byte 0x03000198\n_08052984: .4byte 0x00001818");
}
