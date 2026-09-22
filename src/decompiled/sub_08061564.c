#include "global.h"

void TextDraw(u8 *data)
{
    u8 *cursor;
    u8 opcode;

    if (data == 0 || data[0] == 0)
        return;
    opcode = data[0];
    cursor = data + 1;
    while (opcode != 0)
    {
        if (opcode == 8)
        {
            TextSetPaletteBank(*cursor);
            cursor++;
        }
        else
        {
            if (opcode > 8)
            {
                if (opcode != 10)
                    goto unknown_opcode;
                {
                    struct Unk0798 *work;
                    u16 current;

                    work = gUnk_03000798;
                    work->unk90 = 0;
                    current = work->unk92;
                    current += work->unkA2;
                    work->unk92 = current;
                    if ((s16)current > (work->unk9A >> 3) - 1)
                        work->unk92 = 0;
                }
            }
            else if (opcode != 7)
            {
                goto unknown_opcode;
            }
            TextSetCursor(*cursor++, *cursor++);
            goto next_opcode;
        }
        goto next_opcode;
unknown_opcode:
        _08073C44((void *)(u32)opcode, *(void **)0x080BB644);
next_opcode:
        opcode = *cursor;
        cursor++;
    }
}
