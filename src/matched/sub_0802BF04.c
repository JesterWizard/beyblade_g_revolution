#include "global.h"

// @ 0x0802bf04
__attribute__((naked))
void sub_0802BF04(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r8\npush {r7}\nlsls r0, r0, #0x10\nlsrs r2, r0, #0x10\nlsls r1, r1, #0x18\nlsrs r6, r1, #0x18\nldr r4, _0802BF78 @ =0x03000198\nldr r0, [r4, #0x00]\nldr r3, _0802BF7C @ =0x00001694\nadds r0, r0, r3\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0802BF86\nmovs r1, #0x00\nlsls r0, r2, #0x10\nadds r5, r3, #0x0\nasrs r0, r0, #0x10\nmov r12, r0\nlsls r0, r6, #0x18\nasrs r7, r0, #0x18\nmovs r6, #0xFF\nmov r8, r1\n_0802BF32:\nldr r0, [r4, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nlsls r3, r1, #0x02\nadds r2, r3, r0\nmovs r0, #0x00\nldsb r0, [r2, r0]\ncmp r0, r12\nbne _0802BF80\nmovs r0, #0x03\nldsb r0, [r2, r0]\ncmp r0, r7\nbne _0802BF80\nldrb r0, [r2, #0x00]\norrs r0, r6\nstrb r0, [r2, #0x00]\nldr r0, [r4, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r3, r0\nldrb r1, [r0, #0x03]\norrs r1, r6\nstrb r1, [r0, #0x03]\nldr r0, [r4, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r3, r0\nmov r1, r8\nstrb r1, [r0, #0x02]\nldr r0, [r4, #0x00]\nadds r0, r0, r5\nldr r0, [r0, #0x00]\nadds r0, r3, r0\nstrb r1, [r0, #0x01]\nb _0802BF86\n_0802BF78: .4byte 0x03000198\n_0802BF7C: .4byte 0x00001694\n_0802BF80:\nadds r1, #0x01\ncmp r1, #0x7F\nble _0802BF32\n_0802BF86:\npop {r3}\nmov r8, r3\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
