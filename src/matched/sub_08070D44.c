#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08070d44
/* match-compiler: old_agbcc */
u8 sub_08070D44(struct Unk7069C *a, s32 value, u8 b)
{
    u8 buf[0x10];
    u32 neg;
    u8 commas;
    u8 digits;
    u8 *p;

    neg = 0;
    commas = 3;
    digits = 0x0E;
    if (value < 0) {
        neg = 1;
        value = -value;
    }
    p = buf + 15;
    *p = 0;
    do {
        if (value == 0) {
            *--p = 0x30;
            break;
        }
        if ((a->unk08 & 0x40) == 0) {
            commas--;
            if (commas == 0xFF) {
                *--p = 0x2C;
                commas = 2;
                digits--;
            }
        }
        *--p = (u8)sub_080674A4(value, 10) + 0x30;
        value = sub_080674A0(value, 10);
        digits--;
    } while (value != 0 && digits != 0);
    if (neg != 0)
        *--p = 0x2D;
    return sub_08070930(a, p, b);
}

