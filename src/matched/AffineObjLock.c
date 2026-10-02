#include "global.h"

// @ 0x080705cc
void AffineObjLock(struct AffineObj *a)
{
    a->locked = 1;
}
