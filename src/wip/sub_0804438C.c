#include "global.h"

void sub_0804438C(s8 mode_arg)
{
    s8 mode;
    s32 i;
    s32 value;
    s32 level;
    register u32 dispcnt asm("r5");

    mode = mode_arg;
    sub_080617C4((struct Unk617C4 *)0x08119204, 0x080B7429);
    *(vu16 *)0x050001FE = 0;
    mode = mode_arg;
    if (mode == -1)
    {
        i = 0;
        while (i <= 0x0A)
        {
            value = sub_08060394();
            if (value > 0)
            {
                level = (s32)value - 0x10;
                if (level < 0)
                    level = 0;
                sub_080602C0((u8)level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            i++;
        }
        sub_080602C0(0);
        sub_08062C80();
    }
    else if (mode == 1)
    {
        sub_08046E7C();
        sub_08046E7C();
        sub_08046E7C();
        if (gMainWorkPtr->unk1834 == 1)
            sub_08042718();
        i = 0x0A;
        dispcnt = 0x04000000;
        while (i >= 0)
        {
            value = sub_08060394();
            if (value <= 0xB7)
            {
                level = value + 0x10;
                if (level > 0xB8)
                    level = 0xB8;
                sub_080602C0((u8)level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            *(vu16 *)(dispcnt + 0x50) = 0;
            *(vu16 *)(dispcnt + 0x54) = 0;
            *(vu16 *)dispcnt = gMainWorkPtr->unk0358;
            i--;
        }
        sub_08061308();
        sub_08061628(1, 4, 0x1C, 0x10, 0x1BF);
        sub_080602C0(0xB8);
    }
}
