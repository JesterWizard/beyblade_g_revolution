#include "global.h"

// @ 0x0806225c

void SceneObjMotionStep(struct SceneObjSprite *a)
{
    struct Sprite *target;

    if (a == 0)
        return;
    a->posX += a->velX;
    a->posY += a->velY;
    a->velX += a->accelX;
    a->velY += a->accelY;
    if (a->velX != 0)
    {
        if (a->velX > 0)
            a->velX -= a->drag;
        if (a->velX < 0)
            a->velX += a->drag;
    }
    if (a->velY != 0)
    {
        if (a->velY > 0)
            a->velY -= a->drag;
        if (a->velY < 0)
            a->velY += a->drag;
    }
    if (a->anchor != 0)
    {
        target = a->sprite;
        if (target != 0)
        {
            target->unk08 = a->posX - a->anchor->originX;
            target->unk0C = a->posY - a->anchor->originY;
            TextEntrySetPaletteBank(target, a->paletteBank);
        }
    }
    else
    {
        target = a->sprite;
        if (target != 0)
        {
            target->unk08 = a->posX;
            target->unk0C = a->posY;
            TextEntrySetPaletteBank(target, a->paletteBank);
        }
    }
    if (a->frames != 0)
        sub_08062358(a);
    if (a->unk18 != 0)
        sub_08062640((struct SceneObjSprite *)a);
}

