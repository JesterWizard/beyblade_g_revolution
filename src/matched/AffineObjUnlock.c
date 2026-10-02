#include "global.h"

// @ 0x080705d4
void AffineObjUnlock(struct AffineObj *a)
{
    a->locked = 0;
}
