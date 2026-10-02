#include "global.h"

// @ 0x08062238
void sub_08062238(struct SceneObjSprite *a)
{
    if (a != 0)
    {
        if (a->sprite != 0)
        {
            BtlObjPoolFree(a->sprite);
            a->sprite = 0;
        }
        sub_08062684(a);
    }
}

