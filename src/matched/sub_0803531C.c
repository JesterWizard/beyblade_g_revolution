#include "global.h"

// @ 0x0803531c
__attribute__((naked))
void sub_0803531C(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r4, r0, #0x0\nadds r0, #0x8C\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08035330\nadds r0, r4, #0x0\nmovs r1, #0x00\nbl sub_08035258\n_08035330:\nmovs r1, #0x91\nlsls r1, r1, #0x02\nadds r0, r4, r1\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08035344\nadds r0, r4, #0x0\nmovs r1, #0x02\nbl sub_08035258\n_08035344:\nmovs r1, #0xB4\nlsls r1, r1, #0x01\nadds r0, r4, r1\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08035358\nadds r0, r4, #0x0\nmovs r1, #0x01\nbl sub_08035258\n_08035358:\nldr r0, _0803539C @ =0x000002C5\nadds r5, r4, r0\nmovs r0, #0x01\nldrb r1, [r5, #0x00]\nands r0, r1\ncmp r0, #0x00\nbeq _0803536E\nadds r0, r4, #0x0\nadds r0, #0x1C\nbl sub_08068418\n_0803536E:\nmovs r0, #0x04\nldrb r1, [r5, #0x00]\nands r0, r1\ncmp r0, #0x00\nbeq _08035382\nmovs r1, #0xEA\nlsls r1, r1, #0x01\nadds r0, r4, r1\nbl sub_08068418\n_08035382:\nmovs r0, #0x02\nldrb r5, [r5, #0x00]\nands r0, r5\ncmp r0, #0x00\nbeq _08035394\nadds r0, r4, #0x0\nadds r0, #0xF8\nbl sub_08068418\n_08035394:\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0803539C: .4byte 0x000002C5");
}
