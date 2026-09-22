#include "global.h"

void sub_0804A028(u8 *data)
{
    u8 first;
    u8 second;
    s32 position;
    u16 coordinate;

    first = data[0x2D5];
    second = data[0x2FC];
    if (gMainWorkPtr->unk1855 != 0)
    {
        position = ((s32)(s8)second << 16) + 0x50000;
        coordinate = (u16)((u32)position >> 16);
        sub_08061D68(coordinate, 0x0F, 9, 0x14);
        position = ((s32)(s8)first << 16) + 0x50000;
        coordinate = (u16)((u32)position >> 16);
        sub_08061D68(coordinate, 0x0E, 9, 0x14);
    }
    else
    {
        position = ((s32)(s8)second << 1) + 5;
        coordinate = (u16)position;
        sub_08061D68(coordinate, 0x0F, 9, 0x14);
        position += 6;
        coordinate = (u16)position;
        sub_08061D68(coordinate, 0x0F, 9, 0x14);
        position = ((s32)(s8)first << 1) + 5;
        coordinate = (u16)position;
        sub_08061D68(coordinate, 0x0E, 9, 0x14);
        position += 6;
        coordinate = (u16)position;
        sub_08061D68(coordinate, 0x0E, 9, 0x14);
    }
}
