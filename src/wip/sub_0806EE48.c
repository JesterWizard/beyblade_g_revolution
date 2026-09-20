#include "global.h"

void sub_0806EE48(struct Unk6EE48 *state)
{
    register struct Unk6EE48 *work;
    register void *handler;
    register u8 *flag_ptr;
    void *callback;
    u8 i;

    work = state;
    handler = work->unk224;
    if (handler != 0)
    {
        flag_ptr = &work->unk354;
        if ((*flag_ptr & 1) == 0)
        {
            callback = work->unk344;
            if (callback == 0)
                sub_0806EEC8(work);
            else
                _08073C48(handler, work, callback);
        }
        else
        {
            *flag_ptr &= -2;
        }
    }
    for (i = 0; i < 4; i++)
    {
        if (work->unk220->entries[i].unk00 != 0)
            sub_08068E54(&work->motion[i]);
    }
}
