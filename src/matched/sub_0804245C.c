#include "global.h"

// @ 0x0804245c
__attribute__((naked))
void sub_0804245C(void)
{
    asm(".syntax unified\npush {lr}\nldr r0, _08042480 @ =0x03000198\nldr r1, [r0, #0x00]\nldr r2, _08042484 @ =0x0000182C\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _080424E0\nsubs r2, #0x20\nadds r0, r1, r2\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0804247A\ncmp r0, #0x10\nbne _08042488\n_0804247A:\nbl sub_080424E8\nb _080424E0\n_08042480: .4byte 0x03000198\n_08042484: .4byte 0x0000182C\n_08042488:\nldr r0, _080424A8 @ =0x03000538\nldr r0, [r0, #0x00]\nmovs r1, #0x00\nldsb r1, [r0, r1]\nlsls r1, r1, #0x01\nadds r0, #0x04\nadds r0, r0, r1\nldrh r0, [r0, #0x00]\ncmp r0, #0x02\nbeq _080424BC\ncmp r0, #0x02\nbgt _080424AC\ncmp r0, #0x01\nbeq _080424B6\nb _080424CC\n.byte 0x00, 0x00\n_080424A8: .4byte 0x03000538\n_080424AC:\ncmp r0, #0x04\nbeq _080424C2\ncmp r0, #0x08\nbeq _080424C8\nb _080424CC\n_080424B6:\nbl sub_08042540\nb _080424CC\n_080424BC:\nbl sub_080425B8\nb _080424CC\n_080424C2:\nbl sub_08042630\nb _080424CC\n_080424C8:\nbl sub_080426A4\n_080424CC:\nldr r2, _080424E4 @ =0x03000538\nldr r1, [r2, #0x00]\nldrb r0, [r1, #0x00]\nadds r0, #0x01\nstrb r0, [r1, #0x00]\nldr r1, [r2, #0x00]\nmovs r0, #0x1F\nldrb r2, [r1, #0x00]\nands r0, r2\nstrb r0, [r1, #0x00]\n_080424E0:\npop {r0}\nbx r0\n_080424E4: .4byte 0x03000538");
}
