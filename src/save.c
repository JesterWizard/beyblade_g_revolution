#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08044A8C */
// @ 0x08044a8c
/* match-compiler: old_agbcc */

#define SAVE_FAIL(slot)                            \
    {                                              \
        BtlClearUnk1688Entry(slot);                \
        SaveSlotWriteDefault(slot);                \
        gData_03000198->unk185B = 1;               \
        gData_03000198->unk185C = 0;               \
    }

s8 SaveDataVerify(void)
{
    u32 *buf;
    u32 **hdrBlock;
    struct Unk45D3CEntry **slotBlock;
    u16 i;
    u16 retry;
    u32 n;
    u8 invalid;

    n = 3;
    gData_03000198->unk185B = 0;
    gData_03000198->unk185C = 1;
    hdrBlock = HeapAlloc(0x18);
    slotBlock = HeapAlloc(0x1F60);
    gData_03000198->unk1688 = (struct Unk1688Entry *)*hdrBlock;
    gData_03000198->unk168C = *slotBlock;
    buf = *hdrBlock;
    EepromSetType(0x40);
    VBlankIntrWait();
    SoundHwStop();
    REG_IME = 0;
    invalid = 0;
    for (i = 0; i < n; i++)
    {
        retry = 0;
        do
        {
            if (EepromReadBlock(i, buf) != 0)
                retry++;
            else
                retry = 0;
            if (retry == 8)
            {
                SoundHwStart();
                REG_IME = 1;
                for (i = 0; i < 1; i++)
                {
                    BtlClearUnk1688Entry(i);
                    SaveSlotWriteDefault(i);
                }
                gData_03000198->unk185B = 1;
                gData_03000198->unk185C = invalid;
                return 0;
            }
        } while (retry != 0);
        buf += 2;
    }
    for (i = 0; i < 1; i++)
        LoadGameSave(i);
    for (i = 0; i < 1; i++)
    {
        SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]);
        if (SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]) == 0)
            gData_03000198->unk185C = 0;
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk04
            != SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]))
            SAVE_FAIL(i);
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk00 != 0xFEEDFACE)
            SAVE_FAIL(i);
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk00 == 0xFEEDFACE
            && ((u32 *)&gData_03000198->unk168C[i])[1] != 0x1F60)
            SAVE_FAIL(i);
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk10 != 0x00370053
            || ((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk14 != 0x00F6009C)
        {
            DebugPrint((void *)0x083A2E04);
            SAVE_FAIL(i);
        }
    }
    SoundHwStart();
    REG_IME = 1;
    return gData_03000198->unk185B;
}

/* fn: sub_08044D8C */
// @ 0x08044d8c
u32 SaveDataChecksum(u32 *a)
{
    u32 sum = 0;
    u32 bound = 0x7D8;
    u32 *p = a + 1;
    u32 i = 1;

    do
    {
        sum += *p++;
        i++;
    } while (i < bound);

    return sum;
}

/* fn: sub_08044F64 */
// @ 0x08044f64
u32 SaveSlotWriteDefault(u32 idx)
{
    u32 product;
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
                EepromWriteBlock(i, table);
                if (EepromVerifyBlock(i, (void *)table) != 0)
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

/* fn: sub_08044FB0 */
// @ 0x08044fb0
// Clear save slot `index` (a 0x1F60-byte Unk45D3CEntry), then fill it from
// its 8-byte EEPROM blocks via sub_08067584, retrying a block while that
// returns nonzero. Eight failures in a row log, drop the slot and return 0.
s32 LoadGameSave(u32 index)
{
    u8 *base;
    u32 y;
    u32 start;
    u32 end;
    s32 streak;
    s32 hit;
    u32 blocks;

    base = (u8 *)&gMainWorkPtr->unk168C[index];
    {
        u32 *src = gData_080BB8BC;
        _08073C4C(0, base, sizeof(struct Unk45D3CEntry), (void *)*src);
    }
    blocks = sizeof(struct Unk45D3CEntry) / 8;
    start = index * blocks + 3;
    end = index * blocks + 0x3EF;
    for (y = start; y < end; y++)
    {
        streak = 0;
        do
        {
            hit = EepromReadBlock(y, base);
            streak++;
            if (hit == 0)
                streak = 0;
            if (streak == 8)
            {
                DebugPrint((void *)0x083A2E30);
                BtlClearUnk1688Entry(index);
                SaveSlotWriteDefault(index);
                return 0;
            }
        } while (streak != 0);
        base += 8;
    }
    return 1;
}

/* fn: sub_08045198 */
// @ 0x08045198
// Serialize MainWork into a save-slot image: scalar fields, the data blocks
// returned by sub_0802B90C / sub_0803EDC8 / sub_08042E78 / sub_080429C0 /
// sub_08043974, both unk16B0 slots and the 0x53 per-record entries. `fresh`
// picks the sub_08045EF0 / sub_08045D3C op codes.
typedef void (*CpuCopyFunc)(const void *, void *, u32);

void SaveDataWrite(struct Unk45198Save *save, u8 fresh)
{
    s32 i;

    SparklesSaveTimers();
    save->unk0004 = 0x1F60;
    save->unk0044 = gData_03000198->bgmVolume;
    save->unk0045 = gData_03000198->sfxVolume;
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
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)CursorHistoryGet(), save->unk1D9C, 0x144);
    ((CpuCopyFunc)gData_080BB8C0[0])((void *)sub_08043974(), save->unk1EF4, 0x18);
    ((CpuCopyFunc)gData_080BB8C0[0])(&gData_03000198->unk15C8, save->unk1EE0, 0x14);
    if (fresh == 0)
    {
        EventByteVarOp(0, 0, 1000, 0);
        EventFlagOp(0, 1002, 0);
    }
    else
    {
        EventByteVarOp(0, 0, 1007, 0);
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

/* fn: sub_08045590 */
// @ 0x08045590
// Load a save-slot image into MainWork (inverse of sub_08045198); record
// stats are rebuilt from the template table gData_0807A1F4.
typedef void (*CpuCopyFunc)(const void *, void *, u32);

void SaveDataRead(struct Unk45198Save *save, u8 fresh)
{
    s32 i;

    gData_03000198->bgmVolume = save->unk0044;
    gData_03000198->sfxVolume = save->unk0045;
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
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk134C, BeybladeCollectionEntry(0), 0xA50);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1D9C, (void *)CursorHistoryGet(), 0x144);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1EF4, (void *)sub_08043974(), 0x18);
    ((CpuCopyFunc)gData_080BB8C0[0])(save->unk1EE0, &gData_03000198->unk15C8, 0x14);
    if (fresh == 0)
    {
        EventByteVarOp(0, 0, 1001, 0);
        EventFlagOp(0, 1003, 0);
    }
    else
    {
        EventByteVarOp(0, 0, 1006, 0);
        EventFlagOp(0, 1005, 0);
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

/* fn: sub_08045A84 */
// @ 0x08045a84
void SaveBufferFree(struct Unk45A84 *a)
{
    if (a->unk08 != 0)
    {
        if (a->unk00 != 0)
            HeapFree(a->unk00);
    }
    a->unk08 = 0;
    a->unk00 = 0;
    a->unk04 = 0;
}

/* fn: sub_08045AA8 */
// @ 0x08045aa8
void SaveBufferCreate(struct Unk45A84 *a)
{
    if (a->unk08 != 0)
        SaveBufferFree(a);
    a->unk00 = HeapAlloc(0xFB << 5);
    if (a->unk00 != 0)
    {
        a->unk04 = *(void **)a->unk00;
        a->unk08 = 1;
        SaveDataWrite(a->unk04, 1);
    }
}

/* fn: sub_08066434 */
// @ 0x08066434
u8 SaveSlotGet(void)
{
    u32 tmp[2];

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x34;
    return *(u8 *)tmp[0];
}
