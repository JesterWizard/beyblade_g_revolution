#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080411ec
/* match-compiler: old_agbcc */
// Menu input dispatch: in mode 0 (repeat-filtered d-pad from sub_08045C5C)
// or mode 1 (raw held keys), run the first handler slot (unk25C..unk270 =
// right/left/up/down/A/B) whose key is down and which is set.
// The _08073C44/_08073C48 calls in retail are libgcc _call_via_rN thunks.
typedef void (*MenuHandler)(struct MenuState *);

void MenuDispatchKeyHandlers(void *arg)
{
    struct MenuState *a = arg;
    u32 flags;

    if (a->unk2D4 != 1)
        return;
    switch (a->unk2D9)
    {
    case 0:
        flags = sub_08045C5C(0x10, 8);
        if ((flags & 0x20) && a->onLeft != NULL)
            ((MenuHandler)a->onLeft)(a);
        else if ((flags & 0x10) && a->onRight != NULL)
            ((MenuHandler)a->onRight)(a);
        else if ((flags & 0x40) && a->onUp != NULL)
            ((MenuHandler)a->onUp)(a);
        else if ((flags & 0x80) && a->onDown != NULL)
            ((MenuHandler)a->onDown)(a);
        else if ((gData_03004060 & 1) && a->onButtonA != NULL)
            ((MenuHandler)a->onButtonA)(a);
        else if ((gData_03004060 & 2) && a->onButtonB != NULL)
            ((MenuHandler)a->onButtonB)(a);
        break;
    case 1:
        if ((gData_03004060 & 0x20) && a->onLeft != NULL)
            ((MenuHandler)a->onLeft)(a);
        else if ((gData_03004060 & 0x10) && a->onRight != NULL)
            ((MenuHandler)a->onRight)(a);
        else if ((gData_03004060 & 0x40) && a->onUp != NULL)
            ((MenuHandler)a->onUp)(a);
        else if ((gData_03004060 & 0x80) && a->onDown != NULL)
            ((MenuHandler)a->onDown)(a);
        else if ((gData_03004060 & 1) && a->onButtonA != NULL)
            ((MenuHandler)a->onButtonA)(a);
        else if ((gData_03004060 & 2) && a->onButtonB != NULL)
            ((MenuHandler)a->onButtonB)(a);
        break;
    }

}

