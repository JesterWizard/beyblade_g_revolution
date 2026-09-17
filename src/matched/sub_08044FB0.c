#include "global.h"

// @ 0x08044fb0
__attribute__((naked))
void sub_08044FB0(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r8\npush {r7}\nadds r7, r0, #0x0\nldr r0, _08045020 @ =0x03000198\nldr r1, [r0, #0x00]\nldr r0, _08045024 @ =0x0000168C\nadds r1, r1, r0\nlsls r0, r7, #0x06\nsubs r0, r0, r7\nlsls r0, r0, #0x02\nsubs r0, r0, r7\nlsls r0, r0, #0x05\nldr r1, [r1, #0x00]\nadds r6, r1, r0\nldr r0, _08045028 @ =0x080BB8BC\nmovs r2, #0xFB\nlsls r2, r2, #0x05\nldr r3, [r0, #0x00]\nmovs r0, #0x00\nadds r1, r6, #0x0\nbl _08073C4C\nmovs r0, #0xFB\nlsls r0, r0, #0x02\nmuls r0, r7\nadds r1, r0, #0x3\nldr r2, _0804502C @ =0x000003EF\nadds r2, r2, r0\nmov r8, r2\nadds r5, r1, #0x0\ncmp r5, r8\nbcs _08045040\n_08044FF2:\nmovs r4, #0x00\n_08044FF4:\nadds r0, r5, #0x0\nadds r1, r6, #0x0\nbl sub_08067584\nadds r4, #0x01\ncmp r0, #0x00\nbne _08045004\nmovs r4, #0x00\n_08045004:\ncmp r4, #0x08\nbne _08045034\nldr r0, _08045030 @ =0x083A2E30\nbl sub_08067B98\nadds r0, r7, #0x0\nbl sub_08044EE8\nadds r0, r7, #0x0\nbl sub_08044F64\nmovs r0, #0x00\nb _08045042\n.byte 0x00, 0x00\n_08045020: .4byte 0x03000198\n_08045024: .4byte 0x0000168C\n_08045028: .4byte 0x080BB8BC\n_0804502C: .4byte 0x000003EF\n_08045030: .4byte 0x083A2E30\n_08045034:\ncmp r4, #0x00\nbne _08044FF4\nadds r6, #0x08\nadds r5, #0x01\ncmp r5, r8\nbcc _08044FF2\n_08045040:\nmovs r0, #0x01\n_08045042:\npop {r3}\nmov r8, r3\npop {r4, r5, r6, r7}\npop {r1}\nbx r1");
}
