#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b2f0
// Draws |value| right to left into the digit sprites of `row`, starting at
// slot `pos` and covering at most `count` slots. Leading zeroes are only
// drawn when `padZero` is set. Returns the number of digits drawn.
u16 DigitRowDraw(struct Unk6B2F0 *row, s32 value, u16 pos, u16 count, u8 padZero)
{
    struct Actor *obj;
    s16 drawn;
    s16 i;
    s32 digit;
    s32 n;

    drawn = 0;
    if (value < 0)
        value = -value;
    n = value;
    if ((s16)pos >= row->unk04)
        return 0;
    for (i = pos; i > (s16)pos - (s16)count; i--)
    {
        obj = &row->unk00[i];
        if (n > 0)
            digit = DivRemainder(n, 10);
        else
            digit = 0;
        if (digit == 0 && n == 0 && drawn != 0)
        {
            if (!padZero)
                break;
            obj->unk70 = (void *)-1;
            sub_0806833C((struct Unk68598 *)obj, 0, 0x34);
            drawn++;
        }
        else
        {
            obj->unk70 = (void *)-1;
            sub_0806833C((struct Unk68598 *)obj, 0, digit + 0x34);
            drawn++;
        }
        if (n > 0)
            n = Div(n, 10);
    }
    return drawn;
}

