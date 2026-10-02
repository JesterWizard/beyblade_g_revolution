#include "global.h"

// @ 0x0803593c
void sub_0803593C(struct BeybladeBodyInit *a, s32 b, s32 c, s32 d, s32 e)
{
    a->posX = c;
    a->posY = d;
    a->posZ = e;
    a->velZ = 0;
    a->velY = 0;
    a->velX = 0;
    a->accelY = 0;
    a->accelX = 0;
    a->accelZ = 0xFFFFFF00;
    a->drag = 7;
    a->unk04 = 0x1000;
    a->unk08 = 0x1000;
    a->unk00 = b;
    a->unk34 = 0xE6;
    a->unk38 = 0x190;
    a->wobbleX = 0;
    a->wobbleY = 0;
    a->wobblePhase = 0;
    a->wobbleSpeed = 0x166;
    a->wobbleAmp = 5;
}
