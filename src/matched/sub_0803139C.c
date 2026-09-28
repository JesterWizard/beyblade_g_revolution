#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803139c

s32 sub_0803139C(struct Unk705DC **array, s32 value, s32 count, void *table, u8 withPoint)
{
    s32 index;
    s32 quotient;
    s32 digits;
    u16 palette;
    s32 digit;

    digits = 0;
    index = digits;

    while (value != 0 && index < count)
    {
        quotient = Div(value, 10);
        digit = value - quotient * 10;
        if (array[index] == NULL)
        {
            array[index] = BtlObjPoolAlloc(0x1C2);
            if (array[index] != NULL)
            {
                palette = PaletteSlotAcquire(table);
                sub_0806FF58(array[index], table, 0, 0, 0, 0, 0, (u16)(index - 0x30));
                if (array[index] != NULL)
                    TextEntrySetPaletteBank(array[index], (u8)palette);
            }
        }
        if (array[index] != NULL)
            array[index]->unk18 = digit;
        value = quotient;
        index++;
    }
    if (withPoint == 1)
    {
        if (array[index] == NULL)
        {
            array[index] = BtlObjPoolAlloc(0x1C2);
            if (array[index] != NULL)
            {
                palette = PaletteSlotAcquire(table);
                sub_0806FF58(array[index], table, 0, 0, 0, 0, 0, (u16)(index - 0x30));
                if (array[index] != NULL)
                    TextEntrySetPaletteBank(array[index], (u8)palette);
            }
        }
        if (array[index] != NULL)
            array[index]->unk18 = 10;
        index++;
    }
    digits = index;
    for (; index < count; index++)
    {
        if (array[index] != NULL)
        {
            sub_08038638((array[index]->unk14 & 0xF000) >> 12);
            BtlObjPoolFree(array[index]);
            array[index] = NULL;
        }
    }
    return digits;
}

