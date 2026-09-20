#include "global.h"

void sub_08045D3C(
    u32 packed,
    u32 operation_arg,
    u32 *out_arg)
{
    u32 operation;
    u32 group;
    u32 bit;
    u32 *out;
    u8 low;
    u32 mask;
    struct Unk45D3CEntry *entry;
    u32 *src;
    u32 *dst;
    s32 i;

    operation = operation_arg;
    out = out_arg;
    low = (u8)packed;
    group = low >> 5;
    bit = low & 0x1F;
    switch (operation)
    {
    case 4:
        *out = gUnk_03000610.words[group] & (1 << bit);
        break;
    case 0:
        dst = &gUnk_03000610.words[7];
        i = 7;
        do
        {
            *dst-- = 0;
            i--;
        } while (i >= 0);
        break;
    case 1:
        mask = 1 << bit;
        gUnk_03000610.words[group] &= ~mask;
        break;
    case 2:
        mask = 1 << bit;
        gUnk_03000610.words[group] |= mask;
        break;
    case 3:
        mask = 1 << bit;
        gUnk_03000610.words[group] ^= mask;
        break;
    case 0x3EA:
    case 0x3EB:
        entry = gMainWorkPtr->unk168C;
        entry += sub_08066434();
        if (operation == 0x3EA)
        {
            src = gUnk_03000610.words;
            dst = entry->words;
        }
        else
        {
            src = entry->words;
            dst = gUnk_03000610.words;
        }
        i = 7;
        do
        {
            *dst++ = *src++;
            i--;
        } while (i >= 0);
        break;
    case 0x3EC:
    case 0x3ED:
        entry = (struct Unk45D3CEntry *)gMainWorkPtr->unk18B8.unk04;
        if (entry == 0)
            break;
        if (operation == 0x3EC)
        {
            src = entry->words;
            dst = gUnk_03000610.words;
        }
        else
        {
            src = gUnk_03000610.words;
            dst = entry->words;
        }
        i = 7;
        do
        {
            *dst++ = *src++;
            i--;
        } while (i >= 0);
        break;
    }
}
