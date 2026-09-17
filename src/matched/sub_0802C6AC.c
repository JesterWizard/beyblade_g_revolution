#include "global.h"

// @ 0x0802c6ac
__attribute__((naked))
void sub_0802C6AC(void)
{
    asm(".syntax unified\npush {lr}\nldr r0, _0802C6F4 @ =0x0833BE48\nldr r1, _0802C6F8 @ =0x0833BE50\nbl sub_08067B98\nldr r1, _0802C6FC @ =0x03000198\nldr r0, [r1, #0x00]\nldr r2, _0802C700 @ =0x000015C8\nadds r0, r0, r2\nmovs r2, #0x00\nstrb r2, [r0, #0x00]\nldr r0, [r1, #0x00]\nldr r3, _0802C704 @ =0x000015C9\nadds r0, r0, r3\nstrb r2, [r0, #0x00]\nldr r0, [r1, #0x00]\nadds r3, #0x01\nadds r0, r0, r3\nstrb r2, [r0, #0x00]\nldr r0, [r1, #0x00]\nadds r3, #0x01\nadds r0, r0, r3\nstrb r2, [r0, #0x00]\nldr r0, [r1, #0x00]\nadds r3, #0x01\nadds r0, r0, r3\nstrb r2, [r0, #0x00]\nldr r0, [r1, #0x00]\nadds r3, #0x04\nadds r1, r0, r3\nstrh r2, [r1, #0x00]\nldr r1, _0802C708 @ =0x000015D2\nadds r0, r0, r1\nstrh r2, [r0, #0x00]\npop {r0}\nbx r0\n_0802C6F4: .4byte 0x0833BE48\n_0802C6F8: .4byte 0x0833BE50\n_0802C6FC: .4byte 0x03000198\n_0802C700: .4byte 0x000015C8\n_0802C704: .4byte 0x000015C9\n_0802C708: .4byte 0x000015D2");
}
