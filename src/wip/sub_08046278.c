#include "global.h"

/*
 * WIP — not byte-matched. Resume from src/wip/sub_08046278.md
 * Sibling MATCH: sub_08046230 (same Unk16B0[2] slots, per-index + conditional).
 * @ 0x08046278
 */
void sub_08046278(void)
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        gMainWorkPtr->unk16B0[i].unk00 = 0;
        gMainWorkPtr->unk16B0[i].unk04 = -1;
        gMainWorkPtr->unk16B0[i].unk08 = -1;
    }
}
