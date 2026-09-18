#include "global.h"

// @ 0x080338f0
__attribute__((naked))
void sub_080338F0(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadds r2, r0, #0x0\nlsls r1, r1, #0x10\nlsrs r4, r1, #0x10\nldr r0, [r2, #0x04]\nadds r6, r0, #0x4\nmovs r3, #0x00\nldsh r1, [r2, r3]\nldr r0, [r0, #0x00]\ncmp r1, r0\nbne _08033910\nldr r0, _0803390C @ =0x0000FFFF\nb _08033950\n.byte 0x00, 0x00\n_0803390C: .4byte 0x0000FFFF\n_08033910:\nmovs r7, #0x00\nldsh r3, [r2, r7]\nmovs r0, #0x01\nnegs r0, r0\nldrh r5, [r2, #0x00]\ncmp r3, r0\nbeq _08033952\nldrh r1, [r2, #0x02]\nmovs r7, #0x02\nldsh r0, [r2, r7]\ncmp r0, #0x00\nbne _0803392E\ncmp r3, #0x00\nbne _08033952\nb _08033932\n_0803392E:\nsubs r0, r1, #0x1\nstrh r0, [r2, #0x02]\n_08033932:\nmovs r1, #0x00\nldsh r0, [r2, r1]\nlsls r0, r0, #0x01\nadds r0, r0, r6\nldrh r0, [r0, #0x00]\ncmp r4, r0\nbne _08033948\nmovs r0, #0x3C\nstrh r0, [r2, #0x02]\nadds r0, r5, #0x1\nb _08033950\n_08033948:\ncmp r4, #0x00\nbeq _08033952\nmovs r0, #0x00\nstrh r0, [r2, #0x02]\n_08033950:\nstrh r0, [r2, #0x00]\n_08033952:\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
