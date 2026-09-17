#include "global.h"

// @ 0x0805d99c
__attribute__((naked))
void sub_0805D99C(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r1, r0, #0x0\nldr r0, _0805D9E0 @ =0x03000748\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0805D9DA\nstr r1, [r0, #0x0C]\nmovs r0, #0x1B\nbl sub_08066390\nldr r5, _0805D9E4 @ =0x03000198\nldr r4, [r5, #0x00]\nmovs r0, #0xA6\nlsls r0, r0, #0x03\nadds r4, r4, r0\nbl sub_0806639C\nadds r1, r0, #0x0\nadds r0, r4, #0x0\nbl sub_0804109C\nldr r0, [r5, #0x00]\nldr r1, _0805D9E8 @ =0x0000181C\nadds r0, r0, r1\nmovs r2, #0x00\nmovs r1, #0x03\nstrb r1, [r0, #0x00]\nldr r0, [r5, #0x00]\nldr r1, _0805D9EC @ =0x00001708\nadds r0, r0, r1\nstr r2, [r0, #0x00]\n_0805D9DA:\npop {r4, r5}\npop {r0}\nbx r0\n_0805D9E0: .4byte 0x03000748\n_0805D9E4: .4byte 0x03000198\n_0805D9E8: .4byte 0x0000181C\n_0805D9EC: .4byte 0x00001708");
}
