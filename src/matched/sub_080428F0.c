#include "global.h"

// @ 0x080428f0
__attribute__((naked))
void sub_080428F0(u32 a, u32 b, u32 c, u32 d)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r9\nmov r6, r8\npush {r6, r7}\nadds r5, r0, #0x0\nadds r4, r1, #0x0\nadds r6, r2, #0x0\nmov r8, r3\nldr r0, _08042960 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _08042964 @ =0x00001808\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nmovs r1, #0x80\nlsls r1, r1, #0x06\nands r0, r1\ncmp r0, #0x00\nbne _08042984\nbl sub_080428C4\nmovs r3, #0x00\nldr r0, _08042968 @ =0xFFFFFF00\nmov r12, r0\nmovs r7, #0x80\nlsls r7, r7, #0x01\nldr r1, _0804296C @ =0x03000538\nmov r9, r1\n_08042926:\nmov r0, r9\nldr r2, [r0, #0x00]\nlsls r1, r3, #0x01\nadds r0, r2, #0x4\nadds r0, r0, r1\nmov r1, r8\nstrh r1, [r0, #0x00]\nlsls r1, r3, #0x02\nadds r0, r2, #0x0\nadds r0, #0x44\nadds r0, r0, r1\nstr r5, [r0, #0x00]\nadds r0, r2, #0x0\nadds r0, #0xC4\nadds r0, r0, r1\nstr r4, [r0, #0x00]\nldrb r0, [r2, #0x01]\nadds r0, #0x01\nstrb r0, [r2, #0x01]\ncmp r6, #0x01\nbeq _08042974\ncmp r6, #0x01\nbcc _08042970\ncmp r6, #0x02\nbeq _08042978\ncmp r6, #0x03\nbeq _0804297C\nb _0804297E\n.byte 0x00, 0x00\n_08042960: .4byte 0x03000198\n_08042964: .4byte 0x00001808\n_08042968: .4byte 0xFFFFFF00\n_0804296C: .4byte 0x03000538\n_08042970:\nadd r5, r12\nb _0804297E\n_08042974:\nadds r5, r5, r7\nb _0804297E\n_08042978:\nadd r4, r12\nb _0804297E\n_0804297C:\nadds r4, r4, r7\n_0804297E:\nadds r3, #0x01\ncmp r3, #0x0F\nble _08042926\n_08042984:\npop {r3, r4}\nmov r8, r3\nmov r9, r4\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
