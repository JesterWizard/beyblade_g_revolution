#include "global.h"

// @ 0x08033978
__attribute__((naked))
void sub_08033978(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r10\nmov r6, r9\nmov r5, r8\npush {r5, r6, r7}\nmov r9, r0\nadds r4, r1, #0x0\nadds r5, r2, #0x0\nlsls r6, r3, #0x18\nlsrs r6, r6, #0x18\nmovs r7, #0x00\nmovs r0, #0x01\nmov r10, r0\nmov r0, r10\nmov r1, r9\nstrb r0, [r1, #0x00]\nstr r4, [r1, #0x04]\nstr r5, [r1, #0x08]\nldr r1, _08033A24 @ =0x08078158\nlsls r0, r6, #0x02\nadds r0, r0, r1\nldr r1, [r0, #0x00]\nadds r0, r4, #0x0\nbl sub_08034FF8\nldr r1, _08033A28 @ =0x08078E58\nadds r0, r5, #0x0\nadds r2, r4, #0x0\nbl sub_08034FF8\nmovs r0, #0x80\nbl sub_080330F4\nmovs r1, #0x01\nnegs r1, r1\nmov r8, r1\nadds r0, r4, #0x0\nmovs r1, #0x00\nmovs r2, #0x0C\nmov r3, r8\nbl sub_08035204\nadds r0, r4, #0x0\nadds r0, #0x1C\nmovs r1, #0x00\nbl sub_08067FC8\nadds r1, r4, #0x0\nadds r1, #0x8C\nstr r0, [r1, #0x00]\nmovs r1, #0xAC\nlsls r1, r1, #0x02\nadds r0, r4, r1\nstr r7, [r0, #0x00]\nadds r1, #0x04\nadds r0, r4, r1\nmov r1, r8\nstr r1, [r0, #0x00]\nmovs r2, #0xB3\nlsls r2, r2, #0x02\nadds r1, r4, r2\nmovs r0, #0x02\nstr r0, [r1, #0x00]\nmovs r0, #0xC4\nlsls r0, r0, #0x02\nadds r4, r4, r0\nmov r1, r10\nstrb r1, [r4, #0x00]\nadds r5, r5, r2\nmovs r0, #0x06\nstr r0, [r5, #0x00]\nstrb r1, [r4, #0x00]\nmovs r0, #0x0B\nmovs r1, #0x38\nadds r2, r6, #0x0\nbl sub_08060254\nmov r0, r9\nstrb r7, [r0, #0x0D]\npop {r3, r4, r5}\nmov r8, r3\nmov r9, r4\nmov r10, r5\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n_08033A24: .4byte 0x08078158\n_08033A28: .4byte 0x08078E58");
}
