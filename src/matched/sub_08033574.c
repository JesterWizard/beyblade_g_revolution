#include "global.h"

// @ 0x08033574
__attribute__((naked))
void sub_08033574(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nldr r5, _080335B4 @ =0x03000290\nldr r1, [r5, #0x00]\nldr r6, _080335B8 @ =0x00002088\nadds r0, r1, r6\nldrb r0, [r0, #0x00]\ncmp r0, #0x01\nbne _0803359A\nldr r2, _080335BC @ =0x00001FE6\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\nlsrs r4, r0, #0x01\nsubs r2, #0x3A\nadds r0, r1, r2\nbl sub_08068808\nadds r0, r4, #0x0\nbl sub_08038638\n_0803359A:\nldr r0, [r5, #0x00]\nldr r1, _080335C0 @ =0x00002089\nadds r0, r0, r1\nmovs r1, #0xFF\nstrb r1, [r0, #0x00]\nldr r0, [r5, #0x00]\nadds r0, r0, r6\nmovs r1, #0x00\nstrb r1, [r0, #0x00]\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_080335B4: .4byte 0x03000290\n_080335B8: .4byte 0x00002088\n_080335BC: .4byte 0x00001FE6\n_080335C0: .4byte 0x00002089");
}
