#include "global.h"

// @ 0x08043b90
__attribute__((naked))
s32 BtlFindUnk16E0(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r0, _08043BA8 @ =0x03000198\nldr r0, [r0, #0x00]\nmovs r1, #0xB7\nlsls r1, r1, #0x05\nadds r0, r0, r1\nldr r4, [r0, #0x00]\ncmp r4, #0x00\nbne _08043BC6\nmovs r0, #0x01\nnegs r0, r0\nb _08043BCC\n_08043BA8: .4byte 0x03000198\n_08043BAC:\nldr r0, [r4, #0x04]\nb _08043BCC\n_08043BB0:\nldr r0, [r4, #0x00]\nldr r1, _08043BD4 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _08043BD8 @ =0x000016C8\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nbl sub_08073440\ncmp r0, #0x00\nbeq _08043BAC\nadds r4, #0x08\n_08043BC6:\nldr r0, [r4, #0x00]\ncmp r0, #0x00\nbne _08043BB0\n_08043BCC:\npop {r4}\npop {r1}\nbx r1\n.byte 0x00, 0x00\n_08043BD4: .4byte 0x03000198\n_08043BD8: .4byte 0x000016C8");
}
