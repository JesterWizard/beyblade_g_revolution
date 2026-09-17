#include "global.h"

// @ 0x0804737c
__attribute__((naked))
void sub_0804737C(void)
{
    asm(".syntax unified\npush {r4, lr}\nmovs r0, #0x01\nnegs r0, r0\nbl sub_080400C0\nbl sub_08066434\nlsls r0, r0, #0x18\nlsrs r0, r0, #0x18\nbl sub_08045128\nldr r4, _080473D0 @ =0x03000198\nldr r0, [r4, #0x00]\nldr r2, _080473D4 @ =0x0000170C\nadds r1, r0, r2\nadds r2, #0x7C\nadds r0, r0, r2\nldr r1, [r1, #0x00]\nldr r0, [r0, #0x00]\nmuls r0, r1\nldr r1, _080473D8 @ =0xFC96FCDE\nadds r0, r0, r1\nbl sub_080628E4\nldr r0, [r4, #0x00]\nldr r2, _080473DC @ =0x00001819\nadds r0, r0, r2\nldrb r0, [r0, #0x00]\nbl sub_080603A4\nldr r0, [r4, #0x00]\nldr r1, _080473E0 @ =0x0000181A\nadds r0, r0, r1\nldrb r0, [r0, #0x00]\nbl sub_080603E0\nbl sub_080475F4\npop {r4}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080473D0: .4byte 0x03000198\n_080473D4: .4byte 0x0000170C\n_080473D8: .4byte 0xFC96FCDE\n_080473DC: .4byte 0x00001819\n_080473E0: .4byte 0x0000181A");
}
