#include "global.h"

// @ 0x08043bdc
__attribute__((naked))
void sub_08043BDC(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r0, _08043BF0 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _08043BF4 @ =0x000016E4\nadds r0, r0, r1\nldr r4, [r0, #0x00]\ncmp r4, #0x00\nbne _08043C12\nb _08043C18\n.byte 0x00, 0x00\n_08043BF0: .4byte 0x03000198\n_08043BF4: .4byte 0x000016E4\n_08043BF8:\nldr r0, [r4, #0x04]\nb _08043C1A\n_08043BFC:\nldr r0, [r4, #0x00]\nldr r1, _08043C20 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _08043C24 @ =0x000016C8\nadds r1, r1, r2\nldr r1, [r1, #0x00]\nbl sub_08073440\ncmp r0, #0x00\nbeq _08043BF8\nadds r4, #0x08\n_08043C12:\nldr r0, [r4, #0x00]\ncmp r0, #0x00\nbne _08043BFC\n_08043C18:\nmovs r0, #0x00\n_08043C1A:\npop {r4}\npop {r1}\nbx r1\n_08043C20: .4byte 0x03000198\n_08043C24: .4byte 0x000016C8");
}
