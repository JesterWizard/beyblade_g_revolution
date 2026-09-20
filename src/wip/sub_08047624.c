#include "global.h"

s32 sub_08047624(u32 mode_arg)
{
    u8 mode;
    s32 x;
    s32 y;
    s32 value;
    s32 count;

    mode = (u8)mode_arg;
    x = gMainWorkPtr->unk0370 >> 8;
    y = gMainWorkPtr->unk0374 >> 8;
    count = 0;
    switch (mode)
    {
    case 0:
        value = x - 1;
        if ((value & 7) != 0)
        {
            do
            {
                value--;
                count++;
            } while ((value & 7) != 0);
        }
        goto done;
    case 1:
        value = x + 1;
        if ((value & 7) != 0)
        {
            do
            {
                value++;
                count++;
            } while ((value & 7) != 0);
        }
        goto done;
    case 2:
        value = y - 1;
        if ((value & 7) != 0)
        {
            do
            {
                value--;
                count++;
            } while ((value & 7) != 0);
        }
        goto done;
    case 3:
        value = y + 1;
        if ((value & 7) != 0)
        {
            do
            {
                value++;
                count++;
            } while ((value & 7) != 0);
        }
        goto done;
    default:
        goto done;
    }
done:
    return count;
}
