#include "global.h"

// @ 0x080603a4
__attribute__((naked))
void sub_080603A4(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nlsls r0, r0, #0x10\nlsrs r1, r0, #0x10\nadds r4, r1, #0x0\nldr r5, _080603D4 @ =0x03000198\nldr r0, [r5, #0x00]\nldr r2, _080603D8 @ =0x0000177C\nadds r0, r0, r2\nldr r2, [r0, #0x00]\nmovs r0, #0x01\nnegs r0, r0\ncmp r2, r0\nbeq _080603C4\nadds r0, r2, #0x0\nbl sub_08071FC8\n_080603C4:\nldr r0, [r5, #0x00]\nldr r1, _080603DC @ =0x00001819\nadds r0, r0, r1\nstrb r4, [r0, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080603D4: .4byte 0x03000198\n_080603D8: .4byte 0x0000177C\n_080603DC: .4byte 0x00001819");
}
