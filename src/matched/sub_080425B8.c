#include "global.h"

// @ 0x080425b8
__attribute__((naked))
void sub_080425B8(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r4, _0804261C @ =0x03000198\nldr r0, [r4, #0x00]\nldr r1, _08042620 @ =0x00000479\nadds r0, r0, r1\nmovs r1, #0x01\nldrb r2, [r0, #0x00]\norrs r1, r2\nstrb r1, [r0, #0x00]\nldr r5, _08042624 @ =0x03000538\nldr r1, [r5, #0x00]\nmovs r0, #0x20\nstrh r0, [r1, #0x02]\nldr r1, [r4, #0x00]\nldr r2, _08042628 @ =0x00000462\nadds r0, r1, r2\nldrh r0, [r0, #0x00]\ncmp r0, #0x08\nbeq _080425E8\nsubs r2, #0x1A\nadds r0, r1, r2\nmovs r1, #0x08\nbl sub_080680CC\n_080425E8:\nldr r3, [r4, #0x00]\nldr r0, _0804262C @ =0x0000044C\nadds r4, r3, r0\nldr r2, [r5, #0x00]\nmovs r1, #0x00\nldsb r1, [r2, r1]\nlsls r1, r1, #0x02\nadds r0, r2, #0x0\nadds r0, #0x44\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r4, #0x00]\nmovs r1, #0x8A\nlsls r1, r1, #0x03\nadds r3, r3, r1\nmovs r0, #0x00\nldsb r0, [r2, r0]\nlsls r0, r0, #0x02\nadds r2, #0xC4\nadds r2, r2, r0\nldr r0, [r2, #0x00]\nstr r0, [r3, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0804261C: .4byte 0x03000198\n_08042620: .4byte 0x00000479\n_08042624: .4byte 0x03000538\n_08042628: .4byte 0x00000462\n_0804262C: .4byte 0x0000044C");
}
