#include "global.h"

// @ 0x0802b994
__attribute__((naked))
void *sub_0802B994(void)
{
    asm(".syntax unified\nldr r0, _0802B9B4 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0802B9B8 @ =0x00001690\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nldr r3, [r0, #0x00]\nldr r2, _0802B9BC @ =0x0807709C\nldr r0, [r2, #0x04]\ncmp r0, #0x00\nbeq _0802B9CA\nadds r1, r2, #0x4\n_0802B9AA:\nldr r0, [r2, #0x00]\ncmp r0, r3\nbne _0802B9C0\nldr r0, [r1, #0x00]\nb _0802B9CC\n_0802B9B4: .4byte 0x03000198\n_0802B9B8: .4byte 0x00001690\n_0802B9BC: .4byte 0x0807709C\n_0802B9C0:\nadds r1, #0x08\nadds r2, #0x08\nldr r0, [r1, #0x00]\ncmp r0, #0x00\nbne _0802B9AA\n_0802B9CA:\nmovs r0, #0x00\n_0802B9CC:\nbx lr");
}
