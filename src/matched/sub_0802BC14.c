#include "global.h"

// @ 0x0802bc14
__attribute__((naked))
s32 sub_0802BC14(u32 a)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nadds r4, r0, #0x0\nlsls r4, r4, #0x10\nlsrs r4, r4, #0x10\nlsls r5, r4, #0x18\nasrs r5, r5, #0x18\nadds r0, r5, #0x0\nbl sub_0802C62C\nadds r6, r0, #0x0\nadds r0, r5, #0x0\nbl _0802BA7C\nadds r5, r0, #0x0\nldr r0, _0802BC64 @ =0x0833BE30\nlsls r4, r4, #0x10\nasrs r4, r4, #0x10\nadds r1, r4, #0x0\nadds r2, r6, #0x0\nadds r3, r5, #0x0\nbl sub_08067B98\ncmp r6, r5\nbge _0802BC7C\nldr r0, _0802BC68 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0802BC6C @ =0x00001694\nadds r0, r0, r1\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0802BC7C\nmovs r2, #0x00\nadds r1, r0, #0x0\nldr r3, _0802BC70 @ =0xFF0000FF\n_0802BC58:\nldr r0, [r1, #0x00]\ncmp r0, r3\nbne _0802BC74\nmovs r0, #0x00\nb _0802BC7E\n.byte 0x00, 0x00\n_0802BC64: .4byte 0x0833BE30\n_0802BC68: .4byte 0x03000198\n_0802BC6C: .4byte 0x00001694\n_0802BC70: .4byte 0xFF0000FF\n_0802BC74:\nadds r1, #0x04\nadds r2, #0x01\ncmp r2, #0x7F\nble _0802BC58\n_0802BC7C:\nmovs r0, #0x01\n_0802BC7E:\npop {r4, r5, r6}\npop {r1}\nbx r1");
}
