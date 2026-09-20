#include "global.h"

// @ 0x08044f64
u32 sub_08044F64(u32 idx)
{
    register u32 product asm("r0");
    u32 i;
    u32 end;
    u32 count;
    u32 table;
    u32 three = 3;

    product = idx * three;
    end = product + 3;
    i = product;
    if (i < end)
    {
        table = 0x08096938;
        do
        {
            count = 0;
            do
            {
                sub_08067634(i, table);
                if (sub_080677A8(i, (void *)table) != 0)
                    count++;
                else
                    count = 0;
                if (count == 8)
                    return 0;
            } while (count != 0);
            i++;
        } while (i < end);
    }
    return 1;
}

