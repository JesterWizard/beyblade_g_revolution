#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062358
// Frame-list animation tick: when the frame timer runs out, advances to the
// next frame (looping for mode 1, stopping for mode 2 at the -1 terminator)
// and pushes the current frame to the attached text entry.
void sub_08062358(struct SceneObjSprite *a)
{
    struct Unk62358Anim *anim;

    if (a == NULL || a->frames == NULL)
        return;
    if (--a->framesLeft > 0)
        return;
    anim = a->frames;
    switch (a->playMode)
    {
    case 1:
        if (anim[++a->frameIndex].unk02 == -1)
        {
            a->curFrame = anim[0].unk00;
            a->framesLeft = anim[0].unk02;
            a->frameIndex = 0;
        }
        else
        {
            a->curFrame = anim[a->frameIndex].unk00;
            a->framesLeft = anim[a->frameIndex].unk02;
        }
        break;
    case 2:
        if (anim[++a->frameIndex].unk02 == -1)
        {
            a->curFrame = anim[a->frameIndex].unk00;
            a->frames = NULL;
        }
        else
        {
            a->curFrame = anim[a->frameIndex].unk00;
            a->framesLeft = anim[a->frameIndex].unk02;
        }
        break;
    }
    if (a->sprite != NULL)
        a->sprite->unk18 = a->curFrame;
}

