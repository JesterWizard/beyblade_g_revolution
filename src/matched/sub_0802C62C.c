#include "global.h"

// @ 0x0802c62c
__attribute__((naked))
s32 sub_0802C62C(u8 a)
{
    asm(".syntax unified\npush {r4, lr}\nlsls r0, r0, #0x18\nlsrs r2, r0, #0x18\nmovs r3, #0x00\nldr r0, _0802C664 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0802C668 @ =0x00001694\nadds r0, r0, r1\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _0802C65A\nlsls r0, r2, #0x18\nasrs r4, r0, #0x18\nmovs r2, #0x7F\n_0802C648:\nmovs r0, #0x03\nldsb r0, [r1, r0]\ncmp r0, r4\nbne _0802C652\nadds r3, #0x01\n_0802C652:\nadds r1, #0x04\nsubs r2, #0x01\ncmp r2, #0x00\nbge _0802C648\n_0802C65A:\nadds r0, r3, #0x0\npop {r4}\npop {r1}\nbx r1\n.byte 0x00, 0x00\n_0802C664: .4byte 0x03000198\n_0802C668: .4byte 0x00001694");
}
