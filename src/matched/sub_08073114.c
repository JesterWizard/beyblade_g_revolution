#include "global.h"

// @ 0x08073114
__attribute__((naked))
void BtlObjTableRemove(void *a)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nadds r3, r0, #0x0\nldr r0, _08073150 @ =0x03004150\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08073174\nmovs r5, #0x00\nldr r0, _08073154 @ =0x03004154\nadds r2, r0, #0x0\nldrb r0, [r2, #0x00]\ncmp r5, r0\nbcs _08073166\nldr r6, _08073158 @ =0x03004158\nadds r4, r1, #0x0\n_08073130:\nldr r1, [r4, #0x00]\ncmp r1, #0x00\nbeq _0807315C\nldr r0, [r1, #0x00]\ncmp r0, r3\nbne _0807315C\nadds r0, r1, #0x0\nbl sub_0806A434\nmovs r0, #0x00\nstr r0, [r4, #0x00]\nldrb r0, [r6, #0x00]\nsubs r0, #0x01\nstrb r0, [r6, #0x00]\nb _08073166\n.byte 0x00, 0x00\n_08073150: .4byte 0x03004150\n_08073154: .4byte 0x03004154\n_08073158: .4byte 0x03004158\n_0807315C:\nadds r4, #0x04\nadds r5, #0x01\nldrb r0, [r2, #0x00]\ncmp r5, r0\nbcc _08073130\n_08073166:\nldr r0, _0807317C @ =0x03004154\nldrb r0, [r0, #0x00]\ncmp r5, r0\nbne _08073174\nldr r0, _08073180 @ =0x083D2690\nbl sub_08067B98\n_08073174:\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0807317C: .4byte 0x03004154\n_08073180: .4byte 0x083D2690");
}
