#include "global.h"

// @ 0x08042390
__attribute__((naked))
void sub_08042390(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r1, [r0, #0x04]\nasrs r2, r1, #0x08\nldr r0, [r0, #0x08]\nasrs r4, r0, #0x08\nldr r0, _080423C4 @ =0x03000198\nldr r3, [r0, #0x00]\nmovs r1, #0xDC\nlsls r1, r1, #0x02\nadds r0, r3, r1\nldr r0, [r0, #0x00]\nasrs r1, r0, #0x08\nmovs r5, #0xDD\nlsls r5, r5, #0x02\nadds r0, r3, r5\nldr r0, [r0, #0x00]\nasrs r0, r0, #0x08\ncmp r1, r2\nbge _080423D2\ncmp r0, r4\nbge _080423C8\nsubs r0, r2, r1\ncmp r0, #0x0B\nble _080423DC\nb _080423CE\n.byte 0x00, 0x00\n_080423C4: .4byte 0x03000198\n_080423C8:\nsubs r0, r2, r1\ncmp r0, #0x0B\nble _080423EA\n_080423CE:\nmovs r0, #0x03\nb _080423EC\n_080423D2:\ncmp r0, r4\nbge _080423E0\nsubs r0, r1, r2\ncmp r0, #0x0B\nbgt _080423E6\n_080423DC:\nmovs r0, #0x01\nb _080423EC\n_080423E0:\nsubs r0, r1, r2\ncmp r0, #0x0B\nble _080423EA\n_080423E6:\nmovs r0, #0x02\nb _080423EC\n_080423EA:\nmovs r0, #0x00\n_080423EC:\npop {r4, r5}\npop {r1}\nbx r1");
}
