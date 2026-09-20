#include "global.h"

// @ 0x0802b994
#include "global.h"

/* match-flags: -fprologue-bugfix */

void *sub_0802B994(void)
{
    u32 key;
    struct Unk7709C *row;
    u32 *value;
    u32 result;

    key = gMainWorkPtr->unk1690->unk00;
    row = (struct Unk7709C *)0x0807709C;
    result = row->unk04;
    if (result != 0)
    {
        value = &row->unk04;
        do
        {
            result = row->unk00;
            if (result == key)
            {
                result = *value;
                goto done;
            }
            value += 2;
            row++;
            result = *value;
        } while (result != 0);
    }
    result = 0;
done:
    return (void *)result;
}
