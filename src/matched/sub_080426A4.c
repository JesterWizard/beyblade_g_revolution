#include "global.h"

// @ 0x080426a4
__attribute__((naked))
void sub_080426A4(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r4, _08042704 @ =0x03000198\nldr r0, [r4, #0x00]\nldr r1, _08042708 @ =0x00000479\nadds r0, r0, r1\nmovs r1, #0x00\nstrb r1, [r0, #0x00]\nldr r5, _0804270C @ =0x03000538\nldr r1, [r5, #0x00]\nmovs r0, #0x80\nlsls r0, r0, #0x01\nstrh r0, [r1, #0x02]\nldr r1, [r4, #0x00]\nldr r2, _08042710 @ =0x00000462\nadds r0, r1, r2\nldrh r0, [r0, #0x00]\ncmp r0, #0x0B\nbeq _080426D2\nsubs r2, #0x1A\nadds r0, r1, r2\nmovs r1, #0x0B\nbl sub_080680CC\n_080426D2:\nldr r3, [r4, #0x00]\nldr r0, _08042714 @ =0x0000044C\nadds r4, r3, r0\nldr r2, [r5, #0x00]\nmovs r1, #0x00\nldsb r1, [r2, r1]\nlsls r1, r1, #0x02\nadds r0, r2, #0x0\nadds r0, #0x44\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nstr r0, [r4, #0x00]\nmovs r1, #0x8A\nlsls r1, r1, #0x03\nadds r3, r3, r1\nmovs r0, #0x00\nldsb r0, [r2, r0]\nlsls r0, r0, #0x02\nadds r2, #0xC4\nadds r2, r2, r0\nldr r0, [r2, #0x00]\nstr r0, [r3, #0x00]\npop {r4, r5}\npop {r0}\nbx r0\n_08042704: .4byte 0x03000198\n_08042708: .4byte 0x00000479\n_0804270C: .4byte 0x03000538\n_08042710: .4byte 0x00000462\n_08042714: .4byte 0x0000044C");
}
