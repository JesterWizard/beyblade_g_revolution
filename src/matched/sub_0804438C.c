#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804438c
// Brightness fade over 11 steps: mode -1 lowers the level by 16 per step;
// mode 1 raises it by 16 per step (capped at 0xB8) while restoring DISPCNT.
void sub_0804438C(s8 mode)
{
    s32 i;
    s32 value;
    s16 level;

    TextSetActiveObject((struct Unk617C4 *)0x08119204, 0x080B7429);
    *(vu16 *)0x050001FE = 0;
    switch (mode)
    {
    case -1:
        i = 0;
        while (i <= 10)
        {
            value = sub_08060394();
            if (value > 0)
            {
                level = value - 0x10;
                if (level < 0)
                    level = 0;
                sub_080602C0(level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            i++;
        }
        sub_080602C0(0);
        sub_08062C80();
        break;
    case 1:
        FieldUpdateFrame(0);
        FieldUpdateFrame(0);
        FieldUpdateFrame(0);
        if (gMainWorkPtr->unk1834 == 1)
            sub_08042718();
        i = 10;
        while (i >= 0)
        {
            value = sub_08060394();
            if (value <= 0xB7)
            {
                level = value + 0x10;
                if (level > 0xB8)
                    level = 0xB8;
                sub_080602C0(level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            REG_BLDCNT = 0;
            REG_BLDY = 0;
            REG_DISPCNT = gMainWorkPtr->unk0358;
            i--;
        }
        sub_08061308();
        TextWindowLayout(1, 4, 0x1C, 0x10, 0x1BF);
        sub_080602C0(0xB8);
        break;
    }
}

