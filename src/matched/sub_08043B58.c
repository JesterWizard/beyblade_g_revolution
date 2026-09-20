#include "global.h"

// @ 0x08043b58
__attribute__((naked))
struct Unk447CC *sub_08043B58(void)
{
    asm(".syntax unified\nldr r0, _08043B78 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _08043B7C @ =0x00001690\nadds r0, r0, r1\nldr r0, [r0, #0x00]\nldr r2, [r0, #0x00]\nldr r0, _08043B80 @ =0x08096794\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08043B8A\nadds r3, r0, #0x4\n_08043B6E:\nldr r0, [r1, #0x00]\ncmp r2, r0\nbne _08043B84\nadds r0, r1, #0x0\nb _08043B8C\n_08043B78: .4byte 0x03000198\n_08043B7C: .4byte 0x00001690\n_08043B80: .4byte 0x08096794\n_08043B84:\nldm r3!, {r1}\ncmp r1, #0x00\nbne _08043B6E\n_08043B8A:\nmovs r0, #0x00\n_08043B8C:\nbx lr");
}
