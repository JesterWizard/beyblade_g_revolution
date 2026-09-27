#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080338f0
// Advances a key-combo tracker by one frame: `key` must match the next entry
// of the combo table within 60 frames of the previous one, or the combo resets.
// Completing the table sets the position to -1.
void sub_080338F0(struct Unk33958 *a, u16 key)
{
    struct Unk338F0Table *table = a->unk04;
    u16 *keys = table->unk04;

    if (a->unk00 == table->unk00)
    {
        a->unk00 = -1;
        return;
    }
    if (a->unk00 == -1)
        return;
    if (a->unk02 == 0)
    {
        if (a->unk00 != 0)
            return;
    }
    else
        a->unk02--;
    if (key == keys[a->unk00])
    {
        a->unk02 = 60;
        a->unk00++;
    }
    else if (key != 0)
    {
        a->unk02 = 0;
        a->unk00 = 0;
    }
}

