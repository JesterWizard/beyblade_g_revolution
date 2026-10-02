#include "global.h"

// @ 0x080447cc
void MapRunEntryScript(void)
{
    struct Unk447CC *p;
    void *v;

    p = MapGetEntry();
    if (p != 0)
    {
        v = p->unk18;
        if (v != 0)
            ScriptRun(0, v);
    }
}

