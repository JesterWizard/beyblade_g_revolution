#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080735dc
s32 sub_08073218(u8 *src, u8 *dst, u32 n);

void TextFormatInt(s32 num, void *dst, u32 n)
{
    u8 buf[0x16];
    u32 sign;
    u8 pos;

    _08075A58(buf, gData_083D26F0, 0x16);
    pos = 0x14;
    sign = 1;
    if (num < 0) {
        num = -num;
        sign = 0;
    }
    if (num == 0)
        sub_08073218(gData_083D2708, dst, n);
    else {
        while (num > 0) {
            u8 digit = DivRemainder(num, 10);
            u8 slot = pos;

            pos = (u8)(pos - 1);
            buf[slot] = digit + 0x30;
            num = Div(num, 10);
        }
        sub_08073218(buf + pos + sign, dst, n);
    }
}
