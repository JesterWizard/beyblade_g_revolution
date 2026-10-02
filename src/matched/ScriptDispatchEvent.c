#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08056d68
// Dispatches a script event by its 16-bit key; the event's arguments start at
// unk08. Key 0x47EE is recognised but ignored.
void ScriptDispatchEvent(struct ScriptEvent *event)
{
    s16 *entry;
    u32 *args;

    switch (event->key)
    {
    case 0x9E3B:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        args = &event->args;
        gMainWorkPtr->unk181D = 0;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(0, 1);
        break;
    case 0xBEE4:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        args = &event->args;
        gMainWorkPtr->unk181D = 1;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(1, 1);
        entry = FindEntryByString(gMainWorkPtr->unk16C8);
        if (entry != NULL)
            gMainWorkPtr->unk1794 = *entry;
        else
            gMainWorkPtr->unk1794 = -1;
        break;
    case 0xCE50:
        args = &event->args;
        gMainWorkPtr->unk16C8 = args;
        sub_08056F84();
        break;
    case 0xE319:
        args = &event->args;
        gMainWorkPtr->unk16C8 = args;
        ScriptRun(0, BtlFindUnk16E4());
        break;
    case 0x6A74:
        gMainWorkPtr->unk1828 = event->args;
        break;
    case 0x5989:
        gMainWorkPtr->unk182C = event->args;
        break;
    case 0x3D73:
        gMainWorkPtr->unk17F7 = event->args;
        gMainWorkPtr->unk17F6 = event->unk0C;
        gMainWorkPtr->unk1834 = 1;
        break;
    case 0xD791:
        args = &event->args;
        gMainWorkPtr->unk181D = 3;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(3, 1);
        break;
    case 0x47EE:
        break;
    }
}

