#include "global.h"

void sub_08045EF0(u32 index_arg, u32 value_arg, u32 operation_arg, u32 *out_arg)
{
    u32 index8;
    u32 value8;
    u32 operation;
    u32 *out;
    u8 *src;
    u8 *dst;
    struct Unk45D3CEntry *entry;
    s32 i;

    index8 = (u8)index_arg;
    value8 = (u8)value_arg;
    operation = operation_arg;
    out = out_arg;
    switch (operation)
    {
    case 5:
        gUnk_03000600.bytes[(s32)(s8)index8] = (u8)value8;
        break;
    case 6:
        for (i = 0; i < 16; i++)
            gUnk_03000600.bytes[i] = 0;
        break;
    case 7:
        gUnk_03000600.bytes[(s32)(s8)index8]++;
        break;
    case 8:
        gUnk_03000600.bytes[(s32)(s8)index8]--;
        break;
    case 9:
        *out = gUnk_03000600.bytes[(s32)(s8)index8] == (u8)value8;
        break;
    case 10:
        *out = (s8)gUnk_03000600.bytes[(s32)(s8)index8] >=
            (s8)(u8)value8;
        break;
    case 0x3E8:
    case 0x3E9:
        entry = gMainWorkPtr->unk168C;
        entry += sub_08066434();
        if (operation == 0x3E8)
        {
            src = gUnk_03000600.bytes;
            dst = entry->bytes_70;
        }
        else
        {
            src = entry->bytes_70;
            dst = gUnk_03000600.bytes;
        }
        for (i = 0; i < 16; i++)
            dst[i] = src[i];
        break;
    case 0x3EE:
    case 0x3EF:
        entry = (struct Unk45D3CEntry *)gMainWorkPtr->unk18B8.unk04;
        if (entry == 0)
            break;
        if (operation == 0x3EE)
        {
            src = entry->bytes_70;
            dst = gUnk_03000600.bytes;
        }
        else
        {
            src = gUnk_03000600.bytes;
            dst = entry->bytes_70;
        }
        for (i = 0; i < 16; i++)
            dst[i] = src[i];
        break;
    }
}
