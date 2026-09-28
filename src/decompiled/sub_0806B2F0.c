/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

u16 sub_0806B2F0(struct Unk6B2F0 *row, s32 value, u16 pos, u16 count, u8 padZero)
{
    struct Unk68574 *obj;
    u16 drawn;
    u16 i;
    s32 digit;

    drawn = 0;
    if (value < 0)
        value = -value;
    if ((s16)pos >= row->unk04)
        return 0;
    for (i = pos; (s16)i > (s16)pos - (s16)count; i--)
    {
        obj = &row->unk00[(s16)i];
        if (value > 0)
            digit = DivRemainder(value, 10);
        else
            digit = 0;
        if (digit == 0 && value == 0 && (s16)drawn != 0)
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
        if (value > 0)
            value = Div(value, 10);
    }
    return drawn;
}
