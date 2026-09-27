#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080411ec
/* match-compiler: old_agbcc */
// Menu input dispatch: in mode 0 (repeat-filtered d-pad from sub_08045C5C)
// or mode 1 (raw held keys), run the first handler slot (unk25C..unk270 =
// right/left/up/down/A/B) whose key is down and which is set.
// The _08073C44/_08073C48 calls in retail are libgcc _call_via_rN thunks.
typedef void (*MenuHandler)(struct Unk40F4C *);

void sub_080411EC(void *arg)
{
    struct Unk40F4C *a = arg;
    u32 flags;

    if (a->unk2D4 != 1)
        return;
    switch (a->unk2D9)
    {
    case 0:
        flags = sub_08045C5C(0x10, 8);
        if ((flags & 0x20) && a->unk25C != NULL)
            ((MenuHandler)a->unk25C)(a);
        else if ((flags & 0x10) && a->unk260 != NULL)
            ((MenuHandler)a->unk260)(a);
        else if ((flags & 0x40) && a->unk264 != NULL)
            ((MenuHandler)a->unk264)(a);
        else if ((flags & 0x80) && a->unk268 != NULL)
            ((MenuHandler)a->unk268)(a);
        else if ((gData_03004060 & 1) && a->unk26C != NULL)
            ((MenuHandler)a->unk26C)(a);
        else if ((gData_03004060 & 2) && a->unk270 != NULL)
            ((MenuHandler)a->unk270)(a);
        break;
    case 1:
        if ((gData_03004060 & 0x20) && a->unk25C != NULL)
            ((MenuHandler)a->unk25C)(a);
        else if ((gData_03004060 & 0x10) && a->unk260 != NULL)
            ((MenuHandler)a->unk260)(a);
        else if ((gData_03004060 & 0x40) && a->unk264 != NULL)
            ((MenuHandler)a->unk264)(a);
        else if ((gData_03004060 & 0x80) && a->unk268 != NULL)
            ((MenuHandler)a->unk268)(a);
        else if ((gData_03004060 & 1) && a->unk26C != NULL)
            ((MenuHandler)a->unk26C)(a);
        else if ((gData_03004060 & 2) && a->unk270 != NULL)
            ((MenuHandler)a->unk270)(a);
        break;
    }

}

