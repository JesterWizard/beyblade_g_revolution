#include "global.h"

// @ 0x0806f174
void CameraSetTarget(struct Unk6F174 *a, void *b)
{
    a->unk224 = b;
    if (a->unk348 == 0)
        CameraCenterOnObject((struct MapView *)a, b);
    else
        _08073C4C(b, a, (u32)a, a->unk348);
}

