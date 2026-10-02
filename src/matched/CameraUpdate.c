#include "global.h"

// @ 0x0806ee48
// Handler/callback dispatch plus a 4-slot motion scan. skipFollow (set by
// CameraCenterOnObject after a snap) suppresses one follow step.
void CameraUpdate(struct MapView *state)
{
    struct MapView *work;
    void *handler;
    void *callback;
    u8 i;

    work = state;
    handler = work->target;
    if (handler != 0)
    {
        if (!work->skipFollow)
        {
            callback = work->targetHandler;
            if (callback == 0)
                CameraEaseToTarget(work);
            else
                _08073C48(handler, work, callback);
        }
        else
            work->skipFollow = 0;
    }
    for (i = 0; i < 4; i++)
    {
        if (work->follow->entries[i].active != 0)
            sub_08068E54(&work->layers[i]);
    }
}
