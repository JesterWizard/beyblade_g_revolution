#include "global.h"

// @ 0x0802d52c
__attribute__((naked))
void sub_0802D52C(void)
{
    asm(".syntax unified\npush {r4, lr}\nadds r2, r0, #0x0\nadds r4, r1, #0x0\ncmp r4, #0x00\nbeq _0802D578\nldr r0, _0802D568 @ =0x0300026C\nldr r1, [r0, #0x00]\nldr r0, [r1, #0x00]\ncmp r0, #0x00\nbne _0802D584\nldr r0, [r1, #0x08]\nstrh r2, [r0, #0x18]\nldr r0, [r1, #0x08]\nldr r1, _0802D56C @ =0x03000198\nldr r2, [r1, #0x00]\nldr r1, _0802D570 @ =0x00000424\nadds r2, r2, r1\nldr r1, [r2, #0x00]\nldr r1, [r1, #0x08]\nldr r3, _0802D574 @ =0xFFFFF800\nadds r1, r1, r3\nstr r1, [r0, #0x08]\nldr r1, [r2, #0x00]\nldr r1, [r1, #0x0C]\nadds r1, r1, r3\nstr r1, [r0, #0x0C]\nmovs r1, #0x02\nbl sub_080705DC\nb _0802D584\n_0802D568: .4byte 0x0300026C\n_0802D56C: .4byte 0x03000198\n_0802D570: .4byte 0x00000424\n_0802D574: .4byte 0xFFFFF800\n_0802D578:\nldr r0, _0802D590 @ =0x0300026C\nldr r0, [r0, #0x00]\nldr r1, [r0, #0x08]\nldr r0, _0802D594 @ =0xFFFFC000\nstr r0, [r1, #0x08]\nstr r0, [r1, #0x0C]\n_0802D584:\nldr r0, _0802D590 @ =0x0300026C\nldr r0, [r0, #0x00]\nstr r4, [r0, #0x00]\npop {r4}\npop {r0}\nbx r0\n_0802D590: .4byte 0x0300026C\n_0802D594: .4byte 0xFFFFC000");
}
