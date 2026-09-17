#include "global.h"

// @ 0x08033878
__attribute__((naked))
void sub_08033878(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nmovs r5, #0x00\nldr r2, _080338D0 @ =0x03000290\nldr r0, [r2, #0x00]\nldr r3, _080338D4 @ =0x00000B64\nadds r1, r0, r3\nstr r5, [r1, #0x00]\nadds r3, #0x04\nadds r1, r0, r3\nstr r5, [r1, #0x00]\nldr r1, _080338D8 @ =0x00000B6C\nadds r0, r0, r1\nstrb r5, [r0, #0x00]\nldr r0, [r2, #0x00]\nadds r3, #0x08\nadds r1, r0, r3\nstr r5, [r1, #0x00]\nldr r1, _080338DC @ =0x00000B78\nadds r0, r0, r1\nstr r5, [r0, #0x00]\nadds r6, r2, #0x0\n_080338A2:\nldr r0, [r6, #0x00]\nlsls r4, r5, #0x02\nldr r3, _080338E0 @ =0x00000B54\nadds r0, r0, r3\nadds r0, r0, r4\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _080338C2\nbl sub_0806FE84\nldr r0, [r6, #0x00]\nldr r1, _080338E0 @ =0x00000B54\nadds r0, r0, r1\nadds r0, r0, r4\nmovs r1, #0x00\nstr r1, [r0, #0x00]\n_080338C2:\nadds r5, #0x01\ncmp r5, #0x03\nble _080338A2\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080338D0: .4byte 0x03000290\n_080338D4: .4byte 0x00000B64\n_080338D8: .4byte 0x00000B6C\n_080338DC: .4byte 0x00000B78\n_080338E0: .4byte 0x00000B54");
}
