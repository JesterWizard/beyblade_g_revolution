#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08045590
// Load a save-slot image into MainWork (inverse of sub_08045198); record
// stats are rebuilt from the template table gData_0807A1F4.
typedef void (*CpuCopyFunc)(const void *, void *, u32);

void sub_08045590(struct Unk45198Save *save, u8 fresh)
{
    s32 i;

    gData_03000198->unk1819 = save->unk0044;
    gData_03000198->unk181A = save->unk0045;
    gData_03000198->unk181B = save->unk0046;
    gData_03000198->unk1808 = save->unk0008;
    gData_03000198->unk181F = save->unk0047;
    gData_03000198->unk1820 = save->unk0048;
    gData_03000198->unk17E8 = save->unk0040;
    gData_03000198->unk17EA = save->unk0042;
    gData_03000198->unk1798 = save->unk002C;
    gData_03000198->unk179C = save->unk0030;
    gData_03000198->unk1827 = save->unk0049;
    gData_03000198->unk182D = save->unk0053;
    gData_03000198->unk182C = save->unk004A;
    gData_03000198->unk17B4 = save->unk0034;
    gData_03000198->unk17B8 = save->unk0038;
    gData_03000198->unk1810 = save->unk003C;
    gData_03000198->unk1844 = save->unk004B;
    gData_03000198->unk1850 = save->unk004C;
    gData_03000198->unk17F6 = save->unk004D;
    gData_03000198->unk17F7 = save->unk004E;
    gData_03000198->unk1853 = save->unk004F;
    gData_03000198->unk1854 = save->unk0050;
    gData_03000198->unk1855 = save->unk0051;
    gData_03000198->unk1857 = save->unk0052;
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk0080, gData_03000198->unk1694, 0x200);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk06CC, (void *)sub_0802B90C(), 0xF8);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk07C4, (void *)sub_0803EDC8(0), 0xB88);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk134C, sub_08042E78(0), 0xA50);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1D9C, (void *)sub_080429C0(), 0x144);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1EF4, (void *)sub_08043974(), 0x18);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1EE0, &gData_03000198->unk15C8, 0x14);
    if (fresh == 0)
    {
        sub_08045EF0(0, 0, 1001, 0);
        sub_08045D3C(0, 1003, 0);
    }
    else
    {
        sub_08045EF0(0, 0, 1006, 0);
        sub_08045D3C(0, 1005, 0);
    }
    for (i = 0; i < 2; i++)
    {
        gData_03000198->unk16B0[i].unk04 = save->unk0058[i].unk04;
        gData_03000198->unk16B0[i].unk00 = save->unk0058[i].unk00;
        gData_03000198->unk16B0[i].unk08 = save->unk0058[i].unk08;
    }
    for (i = 0; i <= 0x52; i++)
    {
        gData_03000198->unk087C[i] = save->unk0294[i];
        gData_03000198->unk08D0[i].unk1C = save->unk02E8[i].unk00;
        gData_03000198->unk08D0[i].unk1D = save->unk02E8[i].unk01;
        gData_03000198->unk08D0[i].unk1E = save->unk02E8[i].unk02;
        gData_03000198->unk08D0[i].unk1F = save->unk02E8[i].unk03;
        gData_03000198->unk08D0[i].unk20 = save->unk02E8[i].unk04;
        gData_03000198->unk08D0[i].unk21 = save->unk02E8[i].unk05;
        gData_03000198->unk08D0[i].unk26 = save->unk02E8[i].unk06;
        gData_03000198->unk08D0[i].unk23 = save->unk02E8[i].unk07;
        gData_03000198->unk08D0[i].unk24 = save->unk02E8[i].unk08;
        gData_03000198->unk08D0[i].unk25 = save->unk02E8[i].unk09;
        gData_03000198->unk08D0[i].unk14 = gData_0807A1F4[gData_03000198->unk08D0[i].unk1C].unk14;
        gData_03000198->unk08D0[i].unk18 = gData_0807A1F4[gData_03000198->unk08D0[i].unk1C].unk18;
    }
    gData_03000198->unk0868 = save->unk0280;
    gData_03000198->unk086C = save->unk0284;
    gData_03000198->unk0870 = save->unk0288;
    gData_03000198->unk0876 = save->unk028E;
    gData_03000198->expPoints = save->unk028C;
    gData_03000198->strength = save->unk0290;
    gData_03000198->unk0879 = save->unk0291;
    gData_03000198->unk087A = save->unk0292;
    gData_03000198->unk087B = save->unk0293;
    for (i = 0; i <= 0x52; i++)
        gData_03000198->unk1861[i] = save->unk1F0C[i];
}

