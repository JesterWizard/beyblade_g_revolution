#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08045ef0
/* match-compiler: old_agbcc */
// Byte-variable operations on the 16 script bytes gData_03000600 (`index`):
// 11 set, 5 clear all, 6/7 increment/decrement, 8/9/10 compare ==, <, > into
// *out; 0x3E8/0x3E9 save to / load from the current save slot, 0x3EE/0x3EF
// load from / save to unk18B8.
void sub_08045EF0(u8 index, u8 value, u32 op, u32 *out)
{
    struct Unk45D3CEntry *entry;
    s8 i;

    switch (op)
    {
    case 11:
        gData_03000600.bytes[(s8)index] = value;
        break;
    case 5:
        for (i = 0; i < 16; i++)
            gData_03000600.bytes[i] = 0;
        break;
    case 6:
        gData_03000600.bytes[(s8)index]++;
        break;
    case 7:
        gData_03000600.bytes[(s8)index]--;
        break;
    case 8:
        *out = gData_03000600.bytes[(s8)index] == value;
        break;
    case 9:
        *out = (s8)gData_03000600.bytes[(s8)index] < (s8)value;
        break;
    case 10:
        *out = (s8)gData_03000600.bytes[(s8)index] > (s8)value;
        break;
    case 0x3E8:
        entry = &gMainWorkPtr->unk168C[sub_08066434()];
        for (i = 0; i < 16; i++)
            entry->bytes_70[i] = gData_03000600.bytes[i];
        break;
    case 0x3E9:
        entry = &gMainWorkPtr->unk168C[sub_08066434()];
        for (i = 0; i < 16; i++)
            gData_03000600.bytes[i] = entry->bytes_70[i];
        break;
    case 0x3EE:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            for (i = 0; i < 16; i++)
                gData_03000600.bytes[i] = entry->bytes_70[i];
        }
        break;
    case 0x3EF:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            for (i = 0; i < 16; i++)
                entry->bytes_70[i] = gData_03000600.bytes[i];
        }
        break;
    }
}

