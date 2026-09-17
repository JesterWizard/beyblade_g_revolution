#include "global.h"

// @ 0x08051bbc
__attribute__((naked))
void sub_08051BBC(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nldr r5, _08051C1C @ =0x03000198\nldr r1, [r5, #0x00]\nldr r4, _08051C20 @ =0x000017F0\nadds r2, r1, r4\nmovs r3, #0x00\nmovs r0, #0x10\nstrh r0, [r2, #0x00]\nldr r0, _08051C24 @ =0x000017F2\nadds r1, r1, r0\nstrh r3, [r1, #0x00]\nldr r6, _08051C28 @ =0x04000052\n_08051BD4:\nldr r1, [r5, #0x00]\nadds r3, r1, r4\nldrh r0, [r3, #0x00]\nsubs r0, #0x01\nstrh r0, [r3, #0x00]\nldr r7, _08051C24 @ =0x000017F2\nadds r1, r1, r7\nldrh r0, [r1, #0x00]\nadds r0, #0x01\nstrh r0, [r1, #0x00]\nldr r2, _08051C2C @ =0x04000050\nldr r7, _08051C30 @ =0x00003748\nadds r0, r7, #0x0\nstrh r0, [r2, #0x00]\nldrh r1, [r1, #0x00]\nlsls r0, r1, #0x08\nldrh r3, [r3, #0x00]\norrs r0, r3\nstrh r0, [r6, #0x00]\nbl sub_080674B4\nldr r0, _08051C34 @ =0x080BB888\nldr r0, [r0, #0x00]\nbl _08073C40\nbl sub_0806A6F8\nldr r0, [r5, #0x00]\nadds r0, r0, r4\nldrh r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08051BD4\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08051C1C: .4byte 0x03000198\n_08051C20: .4byte 0x000017F0\n_08051C24: .4byte 0x000017F2\n_08051C28: .4byte 0x04000052\n_08051C2C: .4byte 0x04000050\n_08051C30: .4byte 0x00003748\n_08051C34: .4byte 0x080BB888");
}
