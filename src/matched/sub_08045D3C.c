#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08045d3c
// Event-flag operations on the 256-bit set gData_03000610 (flag `id`):
// 0 clear all, 1 clear, 2 set, 3 toggle, 4 test into *out; 0x3EA/0x3EB save
// to / load from the current save slot, 0x3EC/0x3ED to / from unk18B8.
void EventFlagOp(u8 id, u32 op, u32 *out)
{
    u32 group;
    u8 bit;
    struct Unk45D3CEntry *entry;
    u32 *live;
    u32 *saved;
    s32 i;

    group = id >> 5;
    bit = id & 0x1F;
    switch (op)
    {
    case 0:
        gData_03000610.words[0] = 0;
        gData_03000610.words[1] = 0;
        gData_03000610.words[2] = 0;
        gData_03000610.words[3] = 0;
        gData_03000610.words[4] = 0;
        gData_03000610.words[5] = 0;
        gData_03000610.words[6] = 0;
        gData_03000610.words[7] = 0;
        break;
    case 1:
        gData_03000610.words[group] &= ~(1 << bit);
        break;
    case 2:
        gData_03000610.words[group] |= 1 << bit;
        break;
    case 3:
        gData_03000610.words[group] ^= 1 << bit;
        break;
    case 4:
        *out = gData_03000610.words[group] & (1 << bit);
        break;
    case 0x3EA:
        entry = &gMainWorkPtr->unk168C[sub_08066434()];
        live = gData_03000610.words;
        saved = entry->words;
        for (i = 7; i >= 0; i--)
            *saved++ = *live++;
        break;
    case 0x3EB:
        entry = &gMainWorkPtr->unk168C[sub_08066434()];
        saved = entry->words;
        live = gData_03000610.words;
        for (i = 7; i >= 0; i--)
            *live++ = *saved++;
        break;
    case 0x3EC:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            live = gData_03000610.words;
            saved = entry->words;
            for (i = 7; i >= 0; i--)
                *saved++ = *live++;
        }
        break;
    case 0x3ED:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            saved = entry->words;
            live = gData_03000610.words;
            for (i = 7; i >= 0; i--)
                *live++ = *saved++;
        }
        break;
    }
}

