#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08045198
// Serialize MainWork into a save-slot image: scalar fields, the data blocks
// returned by sub_0802B90C / sub_0803EDC8 / sub_08042E78 / sub_080429C0 /
// sub_08043974, both unk16B0 slots and the 0x53 per-record entries. `fresh`
// picks the sub_08045EF0 / sub_08045D3C op codes.
typedef void (*CpuCopyFunc)(const void *, void *, u32);

void SaveDataWrite(struct Unk45198Save *save, u8 fresh)
{
    s32 i;

    sub_080475C4();
    save->unk0004 = 0x1F60;
    save->unk0044 = gData_03000198->unk1819;
    save->unk0045 = gData_03000198->unk181A;
    save->unk0046 = gData_03000198->unk181B;
    save->unk0008 = gData_03000198->unk1808;
    save->unk0047 = gData_03000198->unk181F;
    save->unk0048 = gData_03000198->unk1820;
    save->unk0040 = gData_03000198->unk17E8;
    save->unk0042 = gData_03000198->unk17EA;
    save->unk002C = gData_03000198->unk1798;
    save->unk0030 = gData_03000198->unk179C;
    save->unk0049 = gData_03000198->unk1827;
    save->unk0053 = gData_03000198->unk182D;
    save->unk004A = gData_03000198->unk182C;
    save->unk0034 = gData_03000198->unk17B4;
    save->unk0038 = gData_03000198->unk17B8;
    save->unk003C = gData_03000198->unk1810;
    save->unk004B = gData_03000198->unk1844;
    save->unk004C = gData_03000198->unk1850;
    save->unk004D = gData_03000198->unk17F6;
    save->unk004E = gData_03000198->unk17F7;
    save->unk004F = gData_03000198->unk1853;
    save->unk0050 = gData_03000198->unk1854;
    save->unk0051 = gData_03000198->unk1855;
    save->unk0052 = gData_03000198->unk1857;
    ((CpuCopyFunc)gData_080BB8C0[0])(gData_03000198->unk1694, save->unk0080, 0x200);
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)sub_0802B90C(), save->unk06CC, 0xF8);
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)sub_0803EDC8(0), save->unk07C4, 0xB88);
    ((CpuCopyFunc)gData_080BB8C0[0])(BeybladeCollectionEntry(0), save->unk134C, 0xA50);
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)sub_080429C0(), save->unk1D9C, 0x144);
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)sub_08043974(), save->unk1EF4, 0x18);
    ((CpuCopyFunc)gData_080BB8C0[0])(&gData_03000198->unk15C8, save->unk1EE0, 0x14);
    if (fresh == 0)
    {
        sub_08045EF0(0, 0, 1000, 0);
        EventFlagOp(0, 1002, 0);
    }
    else
    {
        sub_08045EF0(0, 0, 1007, 0);
        EventFlagOp(0, 1004, 0);
    }
    for (i = 0; i < 2; i++)
    {
        save->unk0058[i].unk04 = gData_03000198->unk16B0[i].unk04;
        save->unk0058[i].unk00 = gData_03000198->unk16B0[i].unk00;
        save->unk0058[i].unk08 = gData_03000198->unk16B0[i].unk08;
    }
    for (i = 0; i <= 0x52; i++)
    {
        save->unk0294[i] = gData_03000198->unk087C[i];
        save->unk02E8[i].unk00 = gData_03000198->unk08D0[i].unk1C;
        save->unk02E8[i].unk01 = gData_03000198->unk08D0[i].unk1D;
        save->unk02E8[i].unk02 = gData_03000198->unk08D0[i].unk1E;
        save->unk02E8[i].unk03 = gData_03000198->unk08D0[i].unk1F;
        save->unk02E8[i].unk04 = gData_03000198->unk08D0[i].unk20;
        save->unk02E8[i].unk05 = gData_03000198->unk08D0[i].unk21;
        save->unk02E8[i].unk06 = gData_03000198->unk08D0[i].unk26;
        save->unk02E8[i].unk07 = gData_03000198->unk08D0[i].unk23;
        save->unk02E8[i].unk08 = gData_03000198->unk08D0[i].unk24;
        save->unk02E8[i].unk09 = gData_03000198->unk08D0[i].unk25;
    }
    save->unk0280 = gData_03000198->unk0868;
    save->unk0284 = gData_03000198->unk086C;
    save->unk0288 = gData_03000198->unk0870;
    save->unk028E = gData_03000198->unk0876;
    save->unk028C = gData_03000198->expPoints;
    save->unk0290 = gData_03000198->strength;
    save->unk0291 = gData_03000198->unk0879;
    save->unk0292 = gData_03000198->unk087A;
    save->unk0293 = gData_03000198->unk087B;
    for (i = 0; i <= 0x52; i++)
        save->unk1F0C[i] = gData_03000198->unk1861[i];
}

