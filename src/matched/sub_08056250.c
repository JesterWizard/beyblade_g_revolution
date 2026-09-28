#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08056250
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Redraws the eight visible rows of the scrolling list: label text for each
// filled row, and for the cursor row an icon sprite plus its palette.
void sub_08056250(struct Unk56250 *a)
{
    s32 i;

    sub_08061784();
    if (gData_0300066C == 0)
        return;
    if (a->unk284 != NULL)
    {
        sub_0806FE84(a->unk284);
        a->unk284 = NULL;
    }
    for (i = 0; i < 8; i++)
    {
        if (gData_03000664[gData_03000674 + i].unk0C > -1)
        {
            sub_080615EC(0, i * 8 + 0x10);
            sub_0806171C(gData_03000664[gData_03000674 + i].unk04, 0x4A, 2);
            if (i == gData_03000678)
            {
                a->unk284 = sub_0806FDD0(0);
                sub_0806FF58(a->unk284, gData_03000664[gData_03000674 + i].unk08, 0x2000, 0x4800, 1, 0, 0, 0);
                sub_080705DC(a->unk284, 0x0F);
                ((CpuCopyFunc)gData_080BB8C0[0])(gData_080779A8[gData_03000664[gData_03000674 + i].unk0C], (void *)0x050003E0, 0x20);
                sub_08061D68((u16)(i + 6), 0x0E, 0x0A, 0x1A);
            }
            else
            {
                sub_08061D68((u16)(i + 6), 0x0F, 0x0A, 0x1A);
            }
        }
    }
}

