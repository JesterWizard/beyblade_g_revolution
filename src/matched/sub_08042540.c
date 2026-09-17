#include "global.h"

// @ 0x08042540
__attribute__((naked))
void sub_08042540(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r4, _080425A4 @ =0x03000198\nldr r1, [r4, #0x00]\nldr r0, _080425A8 @ =0x00000479\nadds r1, r1, r0\nmovs r0, #0x02\nldrb r2, [r1, #0x00]\nands r0, r2\nstrb r0, [r1, #0x00]\nldr r5, _080425AC @ =0x03000538\nldr r1, [r5, #0x00]\nmovs r0, #0x40\nstrh r0, [r1, #0x02]\nldr r1, [r4, #0x00]\nldr r2, _080425B0 @ =0x00000462\nadds r0, r1, r2\nldrh r0, [r0, #0x00]\ncmp r0, #0x08\nbeq _08042570\nsubs r2, #0x1A\nadds r0, r1, r2\nmovs r1, #0x08\nbl sub_080680CC\n_08042570:\nldr r3, [r4, #0x00]\nldr r0, _080425B4 @ =0x0000044C\nadds r4, r3, r0\nldr r2, [r5, #0x00]\nmovs r1, #0x00\nldsb r1, [r2, r1]\nlsls r1, r1, #0x02\nadds r0, r2, #0x0\nadds r0, #0x44\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r4, #0x00]\nmovs r0, #0x8A\nlsls r0, r0, #0x03\nadds r3, r3, r0\nmovs r0, #0x00\nldsb r0, [r2, r0]\nlsls r0, r0, #0x02\nadds r2, #0xC4\nadds r2, r2, r0\nldr r0, [r2, #0x00]\nstr r0, [r3, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080425A4: .4byte 0x03000198\n_080425A8: .4byte 0x00000479\n_080425AC: .4byte 0x03000538\n_080425B0: .4byte 0x00000462\n_080425B4: .4byte 0x0000044C");
}
