#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08073988
/* match-compiler: old_agbcc */

s32 TextMeasureWidth(const u8 *text_arg, const u8 *base_arg, u32 delta_arg, u32 space_arg)
{
    u32 index;
    u32 total;
    u32 ch;

    index = 0;
    total = 0;
    if (!text_arg)
        return 0;
    while (1) {
        ch = text_arg[index];
        index++;
        if (!ch)
            return total;
        switch (ch) {
        case 32:
            total += space_arg;
            break;
        case 7:
            index += 2;
            break;
        case 8:
            index += 1;
            break;
        case 10:
            break;
        default:
            total += delta_arg - base_arg[gData_080BB748[ch]];
            break;
        }
        if (!ch)
            return total;
    }
    return total;
}
