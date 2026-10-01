#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08054120
// Item sprite in palette 14 plus a second sprite whose unk18 is scaled by
// 100 - unk02 of the row's MainWork.unk1694 record.
#define SHOW_SCALED_SPRITE(a, i)                                                                  \
    {                                                                                     \
        TextEntrySetPaletteBank(a->unk274[4], 14);                                        \
        a->unk274[5] = BtlObjPoolAlloc(0);                                                \
        SpriteInitFromTemplate(a->unk274[5], (struct Unk6FF58Src *)0x080F3C9C,            \
                               0x800, 0x2400, 1, 0, 0, 0);                                \
        a->unk274[5]->unk18 = ScaleRatio(100 - (s8)gData_03000198->unk1694[              \
            gData_030006FC[gData_030006F4 + i].unk0E].value, 100, 0xB6);                  \
        TextEntrySetPaletteBank(a->unk274[5], 14);                                        \
    }

// Redraws the eight visible rows of a list whose labels depend on
// MainWork.unk1826 (2, 3 or 7), highlighting the selected row with its sprites.
void sub_08054120(void *arg)
{
    struct Unk65560 *a = arg;
    s32 i;

    if (gData_03000700 == 0)
        return;
    if (a->unk274[4] != NULL)
    {
        BtlObjPoolFree(a->unk274[4]);
        a->unk274[4] = NULL;
    }
    if (a->unk274[5] != NULL)
    {
        BtlObjPoolFree(a->unk274[5]);
        a->unk274[5] = NULL;
    }
    for (i = 0; i < 8; i++)
    {
        if (gData_030006F4 + i >= gData_03000700)
            continue;
        TextSetCursor(0, i * 8 + 0x10);
        if (gData_030006FC[gData_030006F4 + i].unk0C >= 0)
        {
            switch ((s8)gData_03000198->unk1826)
            {
            case 3:
                TextDrawAlign(sub_0803DDB0(gData_030006FC[gData_030006F4 + i].unk0C), 0x42, 2);
                break;
            case 2:
                TextDrawAlign(sub_0803DDD8(gData_030006FC[gData_030006F4 + i].unk0C), 0x42, 2);
                break;
            case 7:
                TextDrawAlign((void *)sub_0803DBD0(gData_030006FC[gData_030006F4 + i].unk0C), 0x42, 2);
                break;
            }
        }
        if (i == gData_030006F8)
        {
            TextRowSetPaletteBank((u16)(i + 6), 0xE, 9, 0x1A);
            switch ((s8)gData_03000198->unk1826)
            {
            case 3:
                a->unk274[4] = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk274[4], (struct Unk6FF58Src *)0x082F9A68, 0x2000, 0x4800, 0, 0, 0, 0);
                SHOW_SCALED_SPRITE(a, i);
                break;
            case 2:
                a->unk274[4] = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk274[4], (struct Unk6FF58Src *)0x082F9B38, 0x2000, 0x4800, 0, 0, 0, 0);
                SHOW_SCALED_SPRITE(a, i);
                break;
            case 7:
                a->unk274[4] = BtlObjPoolAlloc(0);
                SpriteInitFromTemplate(a->unk274[4], (struct Unk6FF58Src *)0x082FA21C, 0x2000, 0x4800, 0, 0, 0, 1);
                TextEntrySetPaletteBank(a->unk274[4], 15);
                ((void (*)(const void *, void *, u32))gData_080BB8C0[0])((void *)0x082FBCE0, (void *)0x050003E0, 0x20);
                break;
            }
        }
        else
        {
            TextRowSetPaletteBank((u16)(i + 6), 0xF, 9, 0x1A);
        }
    }
}

