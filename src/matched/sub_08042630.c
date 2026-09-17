#include "global.h"

// @ 0x08042630
__attribute__((naked))
void sub_08042630(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r4, _08042690 @ =0x03000198\nldr r0, [r4, #0x00]\nldr r1, _08042694 @ =0x00000479\nadds r0, r0, r1\nmovs r1, #0x00\nstrb r1, [r0, #0x00]\nldr r5, _08042698 @ =0x03000538\nldr r1, [r5, #0x00]\nmovs r0, #0x80\nstrh r0, [r1, #0x02]\nldr r1, [r4, #0x00]\nldr r2, _0804269C @ =0x00000462\nadds r0, r1, r2\nldrh r0, [r0, #0x00]\ncmp r0, #0x0A\nbeq _0804265C\nsubs r2, #0x1A\nadds r0, r1, r2\nmovs r1, #0x0A\nbl sub_080680CC\n_0804265C:\nldr r3, [r4, #0x00]\nldr r0, _080426A0 @ =0x0000044C\nadds r4, r3, r0\nldr r2, [r5, #0x00]\nmovs r1, #0x00\nldsb r1, [r2, r1]\nlsls r1, r1, #0x02\nadds r0, r2, #0x0\nadds r0, #0x44\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r4, #0x00]\nmovs r1, #0x8A\nlsls r1, r1, #0x03\nadds r3, r3, r1\nmovs r0, #0x00\nldsb r0, [r2, r0]\nlsls r0, r0, #0x02\nadds r2, #0xC4\nadds r2, r2, r0\nldr r0, [r2, #0x00]\nstr r0, [r3, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08042690: .4byte 0x03000198\n_08042694: .4byte 0x00000479\n_08042698: .4byte 0x03000538\n_0804269C: .4byte 0x00000462\n_080426A0: .4byte 0x0000044C");
}
